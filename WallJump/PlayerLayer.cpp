#include "PlayerLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "Scroll.h"
#include "Player.h"

void PlayerLayer::load() {
	addEntity((new Entity(100))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("player.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(0.5, 10)))
		->addComponent(new PlayerComponent())
		->addComponent(new ScrollComponent()));

	addSystem(new PlayerSystem());
	addSystem(new RenderSystem(0));
}