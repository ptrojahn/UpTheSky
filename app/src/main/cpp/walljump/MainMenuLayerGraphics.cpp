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
#include "AnimationsCommon.h"

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
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>()))
		->addComponent(new TextureComponent({ Texture("menuButtonStore.bmp", "texture", GL_NEAREST) })));
	soundButton = new Entity(0);
	soundButton->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "mainMenuButtonToggle.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))));
	soundButton->addComponent(new TransformComponent(Vector2<float>(6.8, 13.8)));
	soundButton->addComponent(new UniformsComponent({ Uniform("alpha", 1.f), Uniform("second", SharedPreferences::getSharedPreferences().getBoolean("muted")) }));
	soundButton->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()));
	soundButton->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>()));
	soundButton->addComponent(new TextureComponent({ Texture("menuButtonSound.bmp", "texture", GL_NEAREST) }));
	addEntity(soundButton);
	int score = SharedPreferences::getSharedPreferences().getInt("highscore");
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.3125, -0.5, 0.625, 1))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 4)))
		->addComponent(new TextureComponent({ Texture("digits.bmp", "digits", GL_NEAREST) }))
		->addComponent(new UniformsComponent({ Uniform("score", score), Uniform("length", (int)std::to_string(score).length()), Uniform("alpha", 1.f), Uniform("textColor", 1.f, 1.f, 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(updateHighScore, classId<MainMenuLayerLogic>())));

	//Arrows
	Entity* arrowLeft = new Entity(0);
		arrowLeft->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "icon.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-1.f, -1.f, 2.f, 2.f))))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f - 2.5f, getEngine()->getLogicalScreenSize().y / 2.f)))
		->addComponent(new TextureComponent({Texture("menuButtonBack.bmp", "texture", GL_NEAREST)}))
		->addComponent(new UniformsComponent({Uniform("alpha", 1.f)}))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>()))
        ->addComponent(new AnimationComponent({
            AnimationState({
                AnimationChange(&arrowLeft->getComponent<TransformComponent>()->scale.x, 1.f, 0.9f),
                AnimationChange(&arrowLeft->getComponent<TransformComponent>()->scale.y, 1.f, 0.9f)
            }, 0.5f),
            AnimationState({
                AnimationChange(&arrowLeft->getComponent<TransformComponent>()->scale.x, 0.9f, 1.f),
                AnimationChange(&arrowLeft->getComponent<TransformComponent>()->scale.y, 0.9f, 1.f)
            }, 0.5f)
        }, AnimationComponent::Loop));
    addEntity(arrowLeft);

    Entity* arrowRight = new Entity(0);
    arrowRight->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "icon.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-1.f, -1.f, 2.f, 2.f))))
        ->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f + 2.5f, getEngine()->getLogicalScreenSize().y / 2.f), 180.f))
        ->addComponent(new TextureComponent({Texture("menuButtonBack.bmp", "texture", GL_NEAREST)}))
        ->addComponent(new UniformsComponent({Uniform("alpha", 1.f)}))
        ->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
        ->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>()))
        ->addComponent(new AnimationComponent({
            AnimationState({
                 AnimationChange(&arrowRight->getComponent<TransformComponent>()->scale.x, 1.f, 0.9f),
                 AnimationChange(&arrowRight->getComponent<TransformComponent>()->scale.y, 1.f, 0.9f)
            }, 0.5f),
            AnimationState({
                 AnimationChange(&arrowRight->getComponent<TransformComponent>()->scale.x, 0.9f, 1.f),
                 AnimationChange(&arrowRight->getComponent<TransformComponent>()->scale.y, 0.9f, 1.f)
            }, 0.5f)
        }, AnimationComponent::Loop));
    addEntity(arrowRight);

	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}