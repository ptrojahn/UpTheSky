#include "LevelManager.h"

#include "Layer.h"
#include "RenderComponent.h"
#include "Scroll.h"
#include "StaticColliderComponent.h"
#include "GhostWall.h"
#include "UniformsComponent.h"
#include "PlayerLayer.h"
#include "ScoreComponent.h"

float jumpFunction(float length) {
	return (PlayerSystem::gravity / 2)*pow((length / PlayerSystem::jumpVelocity.x), 2) + PlayerSystem::jumpVelocity.y * (length / PlayerSystem::jumpVelocity.x);
}

void LevelManagerSystem::addClutterLeft(Vector2<float> position, float jumpDifficultyReduction, float distance, float minX) {
	int maxWidth = 4;
	float playerPos = jumpFunction(position.x - minX) + position.y;
	if (playerPos < -4.25f - jumpDifficultyReduction || playerPos > 0){
		for (int width = (minX - 0.5f)*2 + 1; width <= maxWidth; width++){
			playerPos = jumpFunction(fabsf(position.x - (0.5f + width*0.5f))) + position.y;
			if (playerPos > -4.25f - jumpDifficultyReduction && playerPos < 0){
				//This is the first width that is not allowed
				maxWidth = width - 1;
				break;
			}
		}
	} else
		maxWidth = (minX - 0.5f) * 2.f;
	std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth);
	float xPos = 0.5f - 4.f + wallWidthGenerator(randDevice) * 0.5f;
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

void LevelManagerSystem::addClutterRight(Vector2<float> position, float jumpDifficultyReduction, float distance, float maxX) {
	int maxWidth = 4;
	float playerPos = jumpFunction(position.x + 1.f - (8.5f - maxX)) + position.y;
	if (playerPos < -4.25f - jumpDifficultyReduction || playerPos > 0){
		for (int width = (8.5f - maxX)*2.f + 1; width <= maxWidth; width++){
			playerPos = jumpFunction(fabsf(position.x + 1.f - (8.5f - width*0.5f))) + position.y;
			if (playerPos > -4.25f - jumpDifficultyReduction && playerPos < 0){
				//This is the first width that is not allowed
				maxWidth = width - 1;
				break;
			}
		}
	} else
		maxWidth = (8.5f - maxX) * 2.f;
	std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth);
	float xPos = 8.5f - wallWidthGenerator(randDevice) * 0.5f;
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

void LevelManagerSystem::addBlocks(LevelManagerHelperComponent* helperComponent, float distance) {
	helperComponent->jumpStartYMin += 2;
	helperComponent->jumpStartYMax += 2;

	int score = 0;
	for (Entity* entity : this->getLayer()->getEngine()->getEntities()){
		if (entity->getComponent<ScoreComponent>()){
			score = *(int*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0];
			break;
		}
	}
	float jumpDifficultyReduction = std::max(0.f, (100 - score) / 50.f);

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
			addClutterRight(Vector2<float>(helperComponent->jumpStartX - 1, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpStartX);
		}
		if (jumpFunction(helperComponent->jumpStartX - helperComponent->jumpDestX - 1) + helperComponent->jumpStartYMin + jumpDifficultyReduction > -2){
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
			int minHeight = 2 + std::max(0, (100 - score) / 50);
			std::uniform_int_distribution<int> wallHeightGenerator(minHeight, minHeight + 2);
			helperComponent->height = wallHeightGenerator(mtEngine)*2;
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 6.5 + rand() % 4 * 0.5;
		} else {
			addClutterLeft(Vector2<float>(helperComponent->jumpStartX - 1, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpDestX);
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
			addClutterLeft(Vector2<float>(helperComponent->jumpStartX, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpStartX);
		}
		if (jumpFunction(helperComponent->jumpDestX - helperComponent->jumpStartX - 1) + helperComponent->jumpStartYMin + jumpDifficultyReduction > -2){
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
			int minHeight = 2 + std::max(0, (100 - score) / 50);
			std::uniform_int_distribution<int> wallHeightGenerator(minHeight, minHeight + 4);
			helperComponent->height = wallHeightGenerator(mtEngine)*2;
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 0.5 + rand() % 4 * 0.5;
		} else {
			addClutterRight(Vector2<float>(helperComponent->jumpStartX, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpDestX);
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
					helperComponent->height = 4;
					helperComponent->jumpDestX = 0.5 + rand() % 4 * 0.5;
					helperComponent->playerPosition = LevelManagerHelperComponent::Right;
					helperComponent->firstUse = false;
					distance -= 2;
				} else{
					for (Entity* entity : engine.getEntities()){
						if (entity->getComponent<ScoreComponent>()){
							UniformsComponent* uniforms = entity->getComponent<UniformsComponent>();
							(*(int*)&uniforms->uniforms[0].data[0])++;
							*(int*)&uniforms->uniforms[1].data[0] = std::to_string(*(int*)&uniforms->uniforms[0].data[0]).length();
							break;
						}
					}
					addBlocks(helperComponent, distance);
				}
			}
			break;
		}
	}

	//Remove entities that are no longer visible
	for (std::vector<Entity*>::iterator iterEntities = engine.getEntities().begin(); iterEntities != engine.getEntities().end();){
		if ((*iterEntities)->getComponent<ScrollComponent>() && (*iterEntities)->getComponent<TransformComponent>()->position.y > engine.getLogicalScreenSize().y){
			if ((*iterEntities)->getComponent<PlayerComponent>())
				iterEntities = PlayerSystem::onPlayerDeath((*iterEntities));
			else
				iterEntities = getLayer()->deleteEntity((*iterEntities));
		} else
			iterEntities++;
	}
}