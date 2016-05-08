#include "PlayerLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "Scroll.h"
#include "Player.h"
#include "GhostWall.h"

void PlayerLayer::load() {
	addEntity((new Entity(100))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("player.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f - 0.5, getEngine()->getLogicalScreenSize().y / 2.f - 1)))
		->addComponent(new PlayerComponent())
		->addComponent(new ScrollComponent()));

	addSystem(new RenderSystem(0));
}