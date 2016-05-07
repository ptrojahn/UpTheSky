#include "LevelManager.h"

#include "Layer.h"
#include "RenderComponent.h"
#include "Scroll.h"
#include "StaticColliderComponent.h"
#include "GhostWall.h"
#include "UniformsComponent.h"

float jumpFunction(float length) {
	return (PlayerSystem::gravity / 2)*pow((length / PlayerSystem::jumpVelocity.x), 2) + PlayerSystem::jumpVelocity.y * (length / PlayerSystem::jumpVelocity.x);
}

void LevelManagerSystem::addBlocks(LevelManagerHelperComponent* helperComponent, float distance) {
	helperComponent->jumpStartYMin += 2;
	helperComponent->jumpStartYMax += 2;

	if (helperComponent->playerPosition == LevelManagerHelperComponent::Right){
		//Player is on the right side
		if (helperComponent->jumpStartYMax - helperComponent->jumpStartYMin + 0.1 < helperComponent->height){
			//extend right wall
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "yellow.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->jumpStartYMin -= 2;
		} else {
			//Right side clutter
			int maxWidth = 4;
			int minWidth = (8.5 - helperComponent->jumpStartX) * 2;
			for (int width = minWidth + 1; width <= maxWidth; width++){
				if (jumpFunction(helperComponent->jumpStartX - (8.5 - width * 0.5)) + helperComponent->jumpStartYMin < 0){
					//This is the first wall width that would cause a collision with the player
					maxWidth = width - 1;
					break;
				}
			}
			std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth - 1);
			float xPos = 8.5 - wallWidthGenerator(mtEngine) * 0.5;
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "green.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
		}
		if (jumpFunction(helperComponent->jumpStartX - helperComponent->jumpDestX - 1) + helperComponent->jumpStartYMin > -2){
			//Start wall on the left side
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX - 4, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX - 4, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->playerPosition = LevelManagerHelperComponent::Left;
			std::uniform_int_distribution<int> wallHeightGenerator(4, 8);
			helperComponent->height = wallHeightGenerator(mtEngine);
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 6.5 + rand() % 4 * 0.5;
		} else {
			//Left side clutter
			int maxWidth = 4;
			if (jumpFunction(helperComponent->jumpStartX - helperComponent->jumpDestX - 1) + (helperComponent->jumpStartYMax - helperComponent->height) + 2 > -2.25){
				int minWidth = (helperComponent->jumpDestX - 0.5) * 2 + 1;
				for (int width = minWidth; width <= maxWidth; width++){
					if (jumpFunction(8.5 - width * 0.5 - helperComponent->jumpStartX - 1) + (helperComponent->jumpStartYMax - helperComponent->height) + 2 > -2.25){
						//This is the first width that is not allowed
						maxWidth = width - 1;
						break;
					}
				}
			}
			std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth);
			float xPos = 0.5 - 4 + wallWidthGenerator(mtEngine) * 0.5;
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "blue.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
		}
	} else {
		//Player is on the left side
		if (helperComponent->jumpStartYMax - helperComponent->jumpStartYMin + 0.1 < helperComponent->height){
			//Extend left wall
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "yellow.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX - 4, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX - 4, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->jumpStartYMin -= 2;
		} else {
			//Left side clutter
			int maxWidth = 4;
			int minWidth = (helperComponent->jumpStartX - 0.5) * 2;
			for (int width = minWidth + 1; width <= maxWidth; width++){
				if (jumpFunction(width * 0.5 + 0.5 - helperComponent->jumpStartX) + helperComponent->jumpStartYMin < 0){
					//This is the first wall width that would cause a collision with the player
					maxWidth = width - 1;
					break;
				}
			}
			std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth);
			float xPos = wallWidthGenerator(mtEngine) * 0.5 - 4 + 0.5;
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "green.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
		}
		if (jumpFunction(helperComponent->jumpDestX - helperComponent->jumpStartX - 1) + helperComponent->jumpStartYMin > -2){
			//Start wall on the right side
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->playerPosition = LevelManagerHelperComponent::Right;
			std::uniform_int_distribution<int> wallHeightGenerator(4, 8);
			helperComponent->height = wallHeightGenerator(mtEngine);
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 0.5 + rand() % 4 * 0.5;
		} else {
			//Right side clutter
			int maxWidth = 4;
			if (jumpFunction(helperComponent->jumpDestX - helperComponent->jumpStartX - 1) + (helperComponent->jumpStartYMax - helperComponent->height) + 2 > -2.25){
				int minWidth = (8.5 - helperComponent->jumpDestX) * 2 + 1;
				for (int width = minWidth; width <= maxWidth; width++){
					if (jumpFunction(8.5 - width * 0.5 - helperComponent->jumpStartX - 1) + (helperComponent->jumpStartYMax - helperComponent->height) + 2 > -2.25){
						//This is the first width that is not allowed
						maxWidth = width - 1;
						break;
					}
				}
			}
			std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth);
			float xPos = 8.5 - wallWidthGenerator(mtEngine) * 0.5;
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "blue.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(xPos, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
		}
	}
}

void LevelManagerSystem::update(LayersEngine& engine) {
	//Add new entities
	for (Entity* entity : engine.getEntities()){
		LevelManagerHelperComponent* helperComponent = entity->getComponent<LevelManagerHelperComponent>();
		if (helperComponent){
			float& distance = entity->getComponent<TransformComponent>()->position.y;
			if (distance > 2){
				distance -= 2;
				float lengthLeft = 1;
				float lengthRight = 1;
				if (helperComponent->firstUse){
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -4 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 4)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 2))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -4 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 2)))
						->addComponent(new ScrollComponent()));
					helperComponent->jumpStartX = 7.5;
					helperComponent->jumpStartYMin = -4;
					helperComponent->jumpStartYMax = 0;
					helperComponent->jumpDestX = 0.5 + rand() % 4 * 0.5;
					helperComponent->playerPosition = LevelManagerHelperComponent::Right;
					helperComponent->firstUse = false;
					distance -= 2;
				} else
					addBlocks(helperComponent, distance);
			}
			break;
		}
	}

	//Remove entities that are no longer visible
	for (std::vector<Entity*>::iterator iterEntities = engine.getEntities().begin(); iterEntities != engine.getEntities().end();){
		if ((*iterEntities)->getComponent<ScrollComponent>() && (*iterEntities)->getComponent<TransformComponent>()->position.y > engine.getLogicalScreenSize().y){
			iterEntities = getLayer()->deleteEntity((*iterEntities));
		} else
			iterEntities++;
	}
}