#include "PlayerLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "ScrollComponent.h"
#include "PlayerComponent.h"
#include "GhostWall.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "ScoreComponent.h"
#include "AnimationSystem.h"
#include "ParticleSystem.h"
#include "OnWaitFinishedComponent.h"
#include "OnWaitFinishedSystem.h"
#include "AnimationComponent.h"
#include "SharedPreferences.h"
#include "OnUpdateSystem.h"
#include "OnUpdateComponent.h"
#include "OnLayerEnabledComponent.h"
#include "OnLayerDisabledComponent.h"
#include "ClassId.h"
#include "GameLayer.h"

void moveMoneyUp(Entity* entity) {
	entity->addComponent(new AnimationComponent({ 
		AnimationState({AnimationChange(&entity->getComponent<TransformComponent>()->position.y, 14.75f, 12.5f)},0.1) 
	}, AnimationComponent::Once));
}

void moveMoneyDown(Entity* entity) {
	entity->addComponent(new AnimationComponent({
		AnimationState({ AnimationChange(&entity->getComponent<TransformComponent>()->position.y, 12.5f, 14.75f) }, 0.1)
	}, AnimationComponent::Once));
}

void updateMoney(Entity* entity) {
	int money = SharedPreferences::getSharedPreferences().getInt("money");
	*(int*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0] = money;
	*(int*)&entity->getComponent<UniformsComponent>()->uniforms[1].data[0] = std::to_string(money).length();
}

void updateScore(Entity* entity) {
	int highscore = SharedPreferences::getSharedPreferences().getInt("highscore");
	UniformsComponent* uniforms = entity->getComponent<UniformsComponent>();
	if ((*(int*)&uniforms->uniforms[0].data[0]) == highscore + 1 && highscore != 0 && *(float*)&uniforms->uniforms[3].data[sizeof(float)] == 1.f){
		//Change score color to red
		*(float*)&uniforms->uniforms[3].data[sizeof(float)] = 0.f;
		*(float*)&uniforms->uniforms[3].data[sizeof(float)*2] = 0.f;

		TransformComponent* transform = entity->getComponent<TransformComponent>();
		entity->addComponent(new AnimationComponent({
			AnimationState({
				AnimationChange(&transform->scale.x, 1.f, 1.2f),
				AnimationChange(&transform->scale.y, 1.f, 1.2f)
			}, 0.2f),
			AnimationState({
				AnimationChange(&transform->scale.x, 1.2f, 1.f),
				AnimationChange(&transform->scale.y, 1.2f, 1.f)
			}, 0.2f)
		}, AnimationComponent::Once));
	}
}

void resetScore(Entity* entity) {
	UniformsComponent* uniforms = entity->getComponent<UniformsComponent>();
	(*(int*)&uniforms->uniforms[0].data[0]) = 0;
	*(int*)&uniforms->uniforms[1].data[0] = 1;
	*(float*)&uniforms->uniforms[3].data[sizeof(float)] = 1.f;
	*(float*)&uniforms->uniforms[3].data[sizeof(float)*2] = 1.f;
}

void PlayerLayer::load() {
	addEntity((new Entity(100))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f - 1, getEngine()->getLogicalScreenSize().y / 2.f - 2), 0, Vector2<float>(2.f, 2.f)))
		->addComponent(new PlayerComponent())
		->addComponent(new ScrollComponent())
		->addComponent(new TextureComponent({ Texture("playerAtlas.bmp", "atlas", GL_NEAREST), Texture("skinColors.bmp", "colors", GL_NEAREST) }))
		->addComponent(new UniformsComponent({ Uniform("color0", SharedPreferences::getSharedPreferences().getInt("color0")), Uniform("color1", SharedPreferences::getSharedPreferences().getInt("color1")), Uniform("color2", SharedPreferences::getSharedPreferences().getInt("color2")), Uniform("atlasIndex", SharedPreferences::getSharedPreferences().getInt("skinIndex")) })));

	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.625, -1, 1.25, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 2)))
		->addComponent(new TextureComponent({ Texture("digits.bmp", "digits", GL_NEAREST) }))
		->addComponent(new UniformsComponent({ Uniform("score", 0), Uniform("length", 1), Uniform("alpha", 1.f), Uniform("textColor", 1.f, 1.f, 1.f) }))
		->addComponent(new OnLayerEnabledComponent(resetScore, classId<GameLayer>()))
		->addComponent(new OnUpdateComponent(updateScore))
		->addComponent(new ScoreComponent()));

	int money = SharedPreferences::getSharedPreferences().getInt("money");
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("money.vert", "money.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 0.625, 1))))
		->addComponent(new TransformComponent(Vector2<float>(0.25, 12.5)))
		->addComponent(new TextureComponent({ Texture("digits.bmp", "digits", GL_NEAREST) }))
		->addComponent(new UniformsComponent({ Uniform("money", money), Uniform("length", (int)std::to_string(money).length()), Uniform("alpha", 1.f) }))
		->addComponent(new OnUpdateComponent(updateMoney))
		->addComponent(new OnLayerDisabledComponent(moveMoneyUp, classId<GameLayer>()))
		->addComponent(new OnLayerEnabledComponent(moveMoneyDown, classId<GameLayer>())));

	addSystem(new OnUpdateSystem(2));
	addSystem(new OnWaitFinishedSystem(12));
	addSystem(new ParticleSystem());
	addSystem(new AnimationSystem(10));
	addSystem(new RenderSystem(0));
}