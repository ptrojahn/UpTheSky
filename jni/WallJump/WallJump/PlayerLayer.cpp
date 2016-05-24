#include "PlayerLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "Scroll.h"
#include "Player.h"
#include "GhostWall.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "ScoreComponent.h"

void PlayerLayer::load() {
	addEntity((new Entity(100))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("player.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f - 0.5, getEngine()->getLogicalScreenSize().y / 2.f - 1)))
		->addComponent(new PlayerComponent())
		->addComponent(new ScrollComponent()));

	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.625, -1, 1.25, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 2)))
		->addComponent(new TextureComponent("numbers.bmp", GL_NEAREST))
		->addComponent(new UniformsComponent({Uniform("score", 0), Uniform("length", 1)}))
		->addComponent(new ScoreComponent()));

	addSystem(new RenderSystem(0));
}