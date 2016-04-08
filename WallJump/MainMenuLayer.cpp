#include "MainMenuLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"

void MainMenuLayer::load() {
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-1, -1, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(1.2, 14.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-1, -1, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(3.4, 14.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-1, -1, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(5.6, 14.8))));
	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("mainMenuButton.vert", "mainMenuButton.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-1, -1, 2, 2))))
		->addComponent(new TransformComponent(Vector2<float>(7.8, 14.8))));

	addSystem(new RenderSystem(0));
}