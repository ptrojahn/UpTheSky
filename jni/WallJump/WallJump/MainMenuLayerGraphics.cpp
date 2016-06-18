#include "MainMenuLayerGraphics.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "OnLayerEnabledComponent.h"
#include "OnLayerDisabledComponent.h"
#include "MainMenuLayerLogic.h"
#include "AnimationComponent.h"
#include "AnimationSystem.h"
#include "SharedPreferences.h"
#include "ScoreComponent.h"

void entityFadeOut(Entity* entity) {
	for (Uniform& uniform : entity->getComponent<UniformsComponent>()->uniforms){
		if (uniform.name == "alpha"){
			entity->addComponent(new AnimationComponent({ AnimationState({ AnimationChange((float*)&uniform.data[0], 1.f, 0.f) }, 0.1f) }, AnimationComponent::Once));
			break;
		}
	}
}

void entityFadeIn(Entity* entity) {
	for (Uniform& uniform : entity->getComponent<UniformsComponent>()->uniforms){
		if (uniform.name == "alpha"){
			entity->addComponent(new AnimationComponent({ AnimationState({ AnimationChange((float*)&uniform.data[0], 0.f, 1.f) }, 0.1f) }, AnimationComponent::Once));
			break;
		}
	}
}

void updateHighScore(Entity* entity) {
	for (Entity* scoreEntity : entity->getLayer()->getEngine()->getEntities()){
		if (scoreEntity->getComponent<ScoreComponent>()){
			int score = *(int*)&scoreEntity->getComponent<UniformsComponent>()->uniforms[0].data[0];
			int& highscore = *(int*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0];
			if (score > highscore){
				SharedPreferences::getSharedPreferences().putInt("highscore", score);
				SharedPreferences::getSharedPreferences().apply();
				highscore = score;
				*(int*)&entity->getComponent<UniformsComponent>()->uniforms[1].data[0] = std::to_string(highscore).length();
			}
		}
	}
	entityFadeIn(entity);
}

void MainMenuLayerGraphics::load() {
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(2.4, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.6, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(6.8, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	int score = SharedPreferences::getSharedPreferences().getInt("highscore", 0);
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.3125, -0.5, 0.625, 1))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 4)))
		->addComponent(new TextureComponent("digits.bmp", GL_NEAREST))
		->addComponent(new UniformsComponent({ Uniform("score", score), Uniform("length", (int)std::to_string(score).length()), Uniform("alpha", 1.f), Uniform("textColor", 0.f, 0.f, 0.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(updateHighScore, classId<MainMenuLayerLogic>())));

	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}