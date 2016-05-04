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
		if (helperComponent->jumpStartYMax - helperComponent->jumpStartYMin < 6){
			//Right side wall
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
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
			helperComponent->jumpStartYMax += 4;
		} else {
			//Right side clutter
			int maxWidth = 4;
			if (helperComponent->jumpStartYMin < -1.5)
				maxWidth = (8.5 - helperComponent->jumpStartX) * 2 + 1;
			else
				for (int width = 0; width < 4; width++){
					if (jumpFunction(helperComponent->jumpStartX - (8.5 - width * 0.5)) + helperComponent->jumpStartYMin < 0){
						//This is the first width that is not allowed
						maxWidth = width;
						break;
					}
				}
			if (maxWidth != 0){
				std::random_device randDevice;
				std::mt19937 mtEngine(randDevice());
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
		}
		if (jumpFunction(helperComponent->jumpStartX - helperComponent->jumpDestX - 0.5 - 1) + helperComponent->jumpStartYMin > -2){
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
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 6.5 + rand() % 4 * 0.5;
		} else {
			SDL_Log("blau starten");
			//left side clutter
			int maxWidth = 4;
			if (helperComponent->jumpStartYMin < -1.5)
				maxWidth = (helperComponent->jumpDestX - 0.5) * 2 + 1;
			else
				for (int width = 0; width < 4; width++){
					if (jumpFunction(width * 0.5 + 0.5 - helperComponent->jumpDestX) + helperComponent->jumpStartYMin < 0){
						//This is the first width that is not allowed
						maxWidth = width;
						SDL_Log("pass: %i", maxWidth);
						break;
					}
				}
			if (maxWidth != 0){
				std::random_device randDevice;
				std::mt19937 mtEngine(randDevice());
				SDL_Log("Width: %i", maxWidth);
				std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth - 1);
				float xPos = wallWidthGenerator(mtEngine) * 0.5 - 4 + 0.5;
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
				SDL_Log("Links blau");
			}
		}
	} else {
		//Player is on the left side
		if (helperComponent->jumpStartYMax - helperComponent->jumpStartYMin < 6){
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
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
			helperComponent->jumpStartYMax += 4;
		} else {
			//left side clutter
			int maxWidth = 4;
			if (helperComponent->jumpStartYMin < -1.5)
				maxWidth = (helperComponent->jumpStartX - 0.5) * 2 + 1;
			else
				for (int width = 0; width < 4; width++){
					if (jumpFunction(width * 0.5 + 0.5 - helperComponent->jumpStartX) + helperComponent->jumpStartYMin < 0){
						//This is the first width that is not allowed
						maxWidth = width;
						break;
					}
				}
			if (maxWidth != 0){
				std::random_device randDevice;
				std::mt19937 mtEngine(randDevice());
				std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth - 1);
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
		}
		if (jumpFunction(helperComponent->jumpDestX - helperComponent->jumpStartX) + helperComponent->jumpStartYMin + 1 > -2){
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
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 0.5 + rand() % 4 * 0.5;
		} else {
			//Right side clutter
			int maxWidth = 4;
			if (helperComponent->jumpStartYMin < -1.5)
				maxWidth = (8.5 - helperComponent->jumpDestX) * 2 + 1;
			else
				for (int width = 0; width < 4; width++){
					if (jumpFunction(helperComponent->jumpDestX - (8.5 - width * 0.5)) + helperComponent->jumpStartYMin < 0){
						//This is the first width that is not allowed
						maxWidth = width;
						break;
					}
				}
			if (maxWidth != 0){
				std::random_device randDevice;
				std::mt19937 mtEngine(randDevice());
				std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth - 1);
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