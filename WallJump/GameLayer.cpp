#include "GameLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "StaticColliderComponent.h"
#include "Scroll.h"
#include "RenderSystem.h"

void GameLayer::load() {
	addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(-3.5, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));
	addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(8.5, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));

	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 3, 3))))
		->addComponent(new TransformComponent(Vector2<float>(6, 13)))
		->addComponent(new StaticColliderComponent(Vector2<float>(3, 3)))
		->addComponent(new ScrollComponent()));
	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 0.5, 4))))
		->addComponent(new TransformComponent(Vector2<float>(6, 9)))
		->addComponent(new StaticColliderComponent(Vector2<float>(0.5, 4)))
		->addComponent(new ScrollComponent()));
	addEntity((new Entity(20000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 3, 7))))
		->addComponent(new TransformComponent(Vector2<float>(0, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(3, 7)))
		->addComponent(new ScrollComponent()));


	addSystem(new ScrollSystem());
	addSystem(new RenderSystem(0));
}