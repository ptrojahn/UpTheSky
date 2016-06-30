#include "PlayerLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "ScrollComponent.h"
#include "Player.h"
#include "GhostWall.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "ScoreComponent.h"
#include "AnimationSystem.h"
#include "ParticleSystem.h"
#include "OnWaitFinishedComponent.h"
#include "OnWaitFinishedSystem.h"
#include "AnimationComponent.h"

void PlayerLayer::load() {
	addEntity((new Entity(100))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "player.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 1, 2))))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f - 1, getEngine()->getLogicalScreenSize().y / 2.f - 2), 0, Vector2<float>(2.f, 2.f)))
		->addComponent(new PlayerComponent())
		->addComponent(new ScrollComponent())
		->addComponent(new TextureComponent({ Texture("playerAtlas.bmp", "atlas", GL_NEAREST), Texture("skinColors.bmp", "colors", GL_NEAREST) }))
		->addComponent(new UniformsComponent({ Uniform("color0", 0), Uniform("color1", 0), Uniform("color2", 0), Uniform("atlasIndex", 13) })));

	addEntity((new Entity(0))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("score.vert", "score.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.625, -1, 1.25, 2))))
		->addComponent(new TransformComponent(Vector2<float>(4.5, 2)))
		->addComponent(new TextureComponent({ Texture("digits.bmp", "digits", GL_NEAREST) }))
		->addComponent(new UniformsComponent({ Uniform("score", 5), Uniform("length", 1), Uniform("alpha", 1.f), Uniform("textColor", 0.f, 0.f, 0.f) }))
		->addComponent(new ScoreComponent()));

	addSystem(new OnWaitFinishedSystem(12));
	addSystem(new ParticleSystem());
	addSystem(new AnimationSystem(10));
	addSystem(new RenderSystem(0));
}