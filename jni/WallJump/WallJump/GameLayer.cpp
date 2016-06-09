#include "GameLayer.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "StaticColliderComponent.h"
#include "GhostWall.h"
#include "ScrollSystem.h"
#include "ScrollComponent.h"
#include "LevelManager.h"
#include "RenderSystem.h"
#include "OnWaitFinishedSystem.h"

void GameLayer::load() {
	//Level generator helper
	addEntity((new Entity(400))
		->addComponent(new LevelManagerHelperComponent())
		->addComponent(new TransformComponent(Vector2<float>(0, 2)))
		->addComponent(new ScrollComponent()));

	addSystem(new OnWaitFinishedSystem(5));
	addSystem(new PlayerSystem());
	addSystem(new GhostWallSystem());
	addSystem(new ScrollSystem());
	addSystem(new LevelManagerSystem());
	addSystem(new RenderSystem(0));
}