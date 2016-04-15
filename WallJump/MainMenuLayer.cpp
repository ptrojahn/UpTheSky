#include "MainMenuLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "StaticColliderComponent.h"
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

	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(-3.5, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));
	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(8.5, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));
	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 3, 3))))
		->addComponent(new TransformComponent(Vector2<float>(6, 13)))
		->addComponent(new StaticColliderComponent(Vector2<float>(3, 3))));
	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 0.5, 4))))
		->addComponent(new TransformComponent(Vector2<float>(6, 9)))
		->addComponent(new StaticColliderComponent(Vector2<float>(0.5, 4))));
	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 3, 7))))
		->addComponent(new TransformComponent(Vector2<float>(0, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(3, 7))));

	addSystem(new RenderSystem(0));
}