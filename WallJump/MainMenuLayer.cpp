#include "MainMenuLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"

void MainMenuLayer::load() {
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(2.4, 13.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.6, 13.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(6.8, 13.8))));

	addSystem(new RenderSystem(0));
}