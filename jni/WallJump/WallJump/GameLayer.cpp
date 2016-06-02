#include "GameLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "StaticColliderComponent.h"
#include "GhostWall.h"
#include "Scroll.h"
#include "LevelManager.h"
#include "RenderSystem.h"

void GameLayer::load() {
	//Level edge
	addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(-3.5, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));
	addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 16))))
		->addComponent(new TransformComponent(Vector2<float>(8.5, 0)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 16))));
	//Level generator helper
	addEntity((new Entity(400))
		->addComponent(new LevelManagerHelperComponent())
		->addComponent(new TransformComponent(Vector2<float>(0, 2)))
		->addComponent(new ScrollComponent()));

	addSystem(new PlayerSystem());
	addSystem(new GhostWallSystem());
	addSystem(new ScrollSystem());
	addSystem(new LevelManagerSystem());
	addSystem(new RenderSystem(0));
}