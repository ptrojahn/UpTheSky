#include "PlayerLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "Player.h"

void PlayerLayer::load() {
	addEntity((new Entity(10000))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("player.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.5, 10)))
		->addComponent(new PlayerComponent()));

	addSystem(new RenderSystem(0));
	addSystem(new PlayerSystem());
}