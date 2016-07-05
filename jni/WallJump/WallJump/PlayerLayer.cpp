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
		->addComponent(new UniformsComponent({ Uniform("score", 5), Uniform("length", 1), Uniform("alpha", 1.f), Uniform("textColor", 0.f, 0.f, 0.f) }))
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