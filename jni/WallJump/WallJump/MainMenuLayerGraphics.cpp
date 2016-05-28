#include "MainMenuLayerGraphics.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "HighScoreComponent.h"
#include "HighScoreUpdateSystem.h"
#include "OnLayerEnabledComponent.h"
#include "OnLayerDisabledComponent.h"
#include "MainMenuLayerLogic.h"
#include "AnimationComponent.h"
#include "AnimationSystem.h"

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

void MainMenuLayerGraphics::load() {
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(2.4, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.6, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(6.8, 13.8)))
		->addComponent(new UniformsComponent({ Uniform("alpha", 1.f) }))
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.3125, -0.5, 0.625, 1))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 4)))
		->addComponent(new TextureComponent("numbers.bmp", GL_NEAREST))
		->addComponent(new UniformsComponent({ Uniform("score", 0), Uniform("length", 1), Uniform("alpha", 1.f) }))
		->addComponent(new HighScoreComponent())
		->addComponent(new OnLayerDisabledComponent(entityFadeOut, classId<MainMenuLayerLogic>()))
		->addComponent(new OnLayerEnabledComponent(entityFadeIn, classId<MainMenuLayerLogic>())));

	addSystem(new HighScoreUpdateSystem());
	addSystem(new AnimationSystem(1));
	addSystem(new RenderSystem(0));
}