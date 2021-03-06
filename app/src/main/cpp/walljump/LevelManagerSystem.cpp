#include "LevelManagerSystem.h"

#include "Layer.h"
#include "RenderComponent.h"
#include "ScrollComponent.h"
#include "StaticColliderComponent.h"
#include "GhostWall.h"
#include "UniformsComponent.h"
#include "PlayerLayer.h"
#include "ScoreComponent.h"
#include "SharedPreferences.h"
#include "AnimationComponent.h"
#include "MersenneTwisterEngine.h"
#include "TextureComponent.h"
#include "CoinComponent.h"
#include "PlayerSystem.h"
#include "PlayerComponent.h"
#include "Vector3.h"

float jumpFunction(float length) {
	return (PlayerSystem::gravity / 2)*pow((length / PlayerSystem::jumpVelocity.x), 2) + PlayerSystem::jumpVelocity.y * (length / PlayerSystem::jumpVelocity.x);
}

bool genHorizontalSpikes(int score) {
	if (score > 75){
		std::uniform_int_distribution<int> horizontalSpikes(0, std::max((200 - (score - 75)) / 20, 1));
		return horizontalSpikes(getMtEngine()) == 0;
	}
	return false;
}

void LevelManagerSystem::genCoin(Vector2<float> position, int score) {
	int value;
	Vector3<float> color;
	if (score > 300){
		value = 3;
		color = Vector3<float>(1.f, 0.1f, 0.1f);
	} else if (score > 150){
		value = 2;
		color = Vector3<float>(0.1f, 1.f, 0.1f);
	} else {
		value = 1;
		color = Vector3<float>(0.1f, 0.1f, 1.f);
	}

	getLayer()->addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "coin.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 0.5, 0.5))))
		->addComponent(new TransformComponent(position))
		->addComponent(new ScrollComponent())
		->addComponent(new CoinComponent())
		->addComponent(new TextureComponent({ Texture("digits.bmp", "digits", GL_NEAREST) }))
		->addComponent(new UniformsComponent({ Uniform("digit", value), Uniform("animationState", 0.f), Uniform("color", color.x, color.y, color.z) })));
}

void LevelManagerSystem::addClutterLeft(Vector2<float> position, float jumpDifficultyReduction, float distance, float minX, int score) {
	bool genRightSpikes = genHorizontalSpikes(score);
	int maxWidth = 4;
	float playerPos = jumpFunction(position.x - (minX + genRightSpikes*0.25f)) + position.y;
	if (playerPos < -4.25f - jumpDifficultyReduction || playerPos > 0){
		for (int width = (minX - 0.5f)*2 + 1; width <= maxWidth; width++){
			playerPos = jumpFunction(fabsf(position.x - (0.5f + width*0.5f + genRightSpikes*0.25f))) + position.y;
			if (playerPos > -4.25f - jumpDifficultyReduction && playerPos < 0){
				//This is the first width that is not allowed
				maxWidth = width - 1;
				break;
			}
		}
	} else
		maxWidth = (minX - 0.5f) * 2.f;

	if (minX == 0.5f + maxWidth*0.5f)
		genRightSpikes = false;

	std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth);
	float xPos = 0.5f - 4.f + wallWidthGenerator(getMtEngine()) * 0.5f;
	getLayer()->addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"),
			BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
		->addComponent(new TransformComponent(Vector2<float>(xPos, -2 + distance)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
		->addComponent(new ScrollComponent()));
	getLayer()->addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_up.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
		->addComponent(new TransformComponent(Vector2<float>(xPos, -2.25 + distance)))
		->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
		->addComponent(new ScrollComponent()));
	if (genRightSpikes){
		getLayer()->addEntity((new Entity(200))
			->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_right.frag"),
			BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 0.25, 2, 1, 8))))
			->addComponent(new TransformComponent(Vector2<float>(xPos + 4, -2 + distance)))
			->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 2)))
			->addComponent(new ScrollComponent()));
	}
}

void LevelManagerSystem::addClutterRight(Vector2<float> position, float jumpDifficultyReduction, float distance, float maxX, int score) {
	bool genLeftSpikes = genHorizontalSpikes(score);
	int maxWidth = 4;
	float playerPos = jumpFunction(position.x + 1.f - (8.5f - (maxX - genLeftSpikes*0.25f))) + position.y;
	if (playerPos < -4.25f - jumpDifficultyReduction || playerPos > 0){
		for (int width = (8.5f - maxX)*2.f + 1; width <= maxWidth; width++){
			playerPos = jumpFunction(fabsf(position.x + 1.f - (8.5f - width*0.5f - genLeftSpikes*0.25f))) + position.y;
			if (playerPos > -4.25f - jumpDifficultyReduction && playerPos < 0){
				//This is the first width that is not allowed
				maxWidth = width - 1;
				break;
			}
		}
	} else 
		maxWidth = (8.5f - maxX) * 2.f;
	
	if (maxX == 8.5f - maxWidth * 0.5f)
		genLeftSpikes = false;

	std::uniform_int_distribution<int> wallWidthGenerator(0, maxWidth);
	float xPos = 8.5f - wallWidthGenerator(getMtEngine()) * 0.5f;
	getLayer()->addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
		->addComponent(new TransformComponent(Vector2<float>(xPos, -2 + distance)))
		->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
		->addComponent(new ScrollComponent()));
	getLayer()->addEntity((new Entity(200))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_up.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
		->addComponent(new TransformComponent(Vector2<float>(xPos, -2.25 + distance)))
		->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
		->addComponent(new ScrollComponent()));
	if (genLeftSpikes){
		getLayer()->addEntity((new Entity(200))
			->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_left.frag"),
			BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 0.25, 2, 1, 8))))
			->addComponent(new TransformComponent(Vector2<float>(xPos -0.25, -2 + distance)))
			->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 2)))
			->addComponent(new ScrollComponent()));
	}
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
	float jumpDifficultyReduction = std::max(0.f, (100 - score) / 50.f) + 0.25;

	if (helperComponent->playerPosition == LevelManagerHelperComponent::Right){
		//Player is on the right side
		if (helperComponent->jumpStartYMax - helperComponent->jumpStartYMin + 0.1 < helperComponent->height){
			//extend right wall
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->jumpStartYMin -= 2;
		} else {
			addClutterRight(Vector2<float>(helperComponent->jumpStartX - 1, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpStartX, score);
		}
		if (jumpFunction(helperComponent->jumpStartX - helperComponent->jumpDestX - 1) + helperComponent->jumpStartYMin + jumpDifficultyReduction > -2){
			//Start wall on the left side
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX - 4, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX - 4, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->playerPosition = LevelManagerHelperComponent::Left;
			int minHeight = 2 + std::max(0, (100 - score) / 50);
			std::uniform_int_distribution<int> wallHeightGenerator(minHeight, minHeight + 2);
			std::uniform_int_distribution<int> wallWidthGenerator(0, 3);
			helperComponent->height = wallHeightGenerator(getMtEngine())*2;
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 6.5 + wallWidthGenerator(getMtEngine()) * 0.5;

			//Generate items
			std::uniform_real_distribution<float> xPosGenerator(0.f, (helperComponent->jumpDestX - helperComponent->jumpStartX) - 1.f);
			float xPos = xPosGenerator(getMtEngine());
			genCoin(Vector2<float>(xPos + helperComponent->jumpStartX + 0.25f, jumpFunction(xPos) - helperComponent->height + PlayerSystem::playerSize.y / 2 - 0.25f), score);
		} else {
			addClutterLeft(Vector2<float>(helperComponent->jumpStartX - 1, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpDestX, score);
		}
	} else {
		//Player is on the left side
		if (helperComponent->jumpStartYMax - helperComponent->jumpStartYMin + 0.1 < helperComponent->height){
			//Extend left wall
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX - 4, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpStartX - 4, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->jumpStartYMin -= 2;
		} else {
			addClutterLeft(Vector2<float>(helperComponent->jumpStartX, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpStartX, score);
		}
		if (jumpFunction(helperComponent->jumpDestX - helperComponent->jumpStartX - 1) + helperComponent->jumpStartYMin + jumpDifficultyReduction > -2){
			//Start wall on the right side
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "levelGeometry.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 2))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX, -2 + distance)))
				->addComponent(new StaticColliderComponent(Vector2<float>(4, 2)))
				->addComponent(new ScrollComponent()));
			getLayer()->addEntity((new Entity(200))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "spikes_up.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
				->addComponent(new TransformComponent(Vector2<float>(helperComponent->jumpDestX, -2.25 + distance)))
				->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
				->addComponent(new ScrollComponent()));
			helperComponent->playerPosition = LevelManagerHelperComponent::Right;
			int minHeight = 2 + std::max(0, (100 - score) / 50);
			std::uniform_int_distribution<int> wallHeightGenerator(minHeight, minHeight + 4);
			std::uniform_int_distribution<int> wallWidthGenerator(0, 3);
			helperComponent->height = wallHeightGenerator(getMtEngine())*2;
			helperComponent->jumpStartYMin = -4 + distance;
			helperComponent->jumpStartYMax = helperComponent->jumpStartYMin + 4;
			helperComponent->jumpStartX = helperComponent->jumpDestX;
			helperComponent->jumpDestX = 0.5 + wallWidthGenerator(getMtEngine()) * 0.5;

			//Generate items
			std::uniform_real_distribution<float> xPosGenerator(0.f, (helperComponent->jumpStartX - helperComponent->jumpDestX) - 1.f);
			float xPos = xPosGenerator(getMtEngine());
			genCoin(Vector2<float>((helperComponent->jumpStartX - helperComponent->jumpDestX) + helperComponent->jumpDestX - 0.75f - xPos, jumpFunction(xPos) - helperComponent->height + PlayerSystem::playerSize.y / 2 - 0.25f), score);
		} else {
			addClutterRight(Vector2<float>(helperComponent->jumpStartX, helperComponent->jumpStartYMax - helperComponent->height), jumpDifficultyReduction, distance, helperComponent->jumpDestX, score);
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
					std::uniform_int_distribution<int> wallHeightGenerator(2, 4);
					helperComponent->height = wallHeightGenerator(getMtEngine()) * 2;
					helperComponent->jumpStartYMin = 0;
					helperComponent->jumpStartYMax = 2;
					helperComponent->firstUse = false;

					std::uniform_int_distribution<int> boolGenerator(0, 1);
					bool left = boolGenerator(getMtEngine());
					std::uniform_int_distribution<int> wallWidthGenerator(0, 4);
					if (left){
						helperComponent->jumpStartX = 0.5;
						helperComponent->jumpDestX = 8.5 - wallWidthGenerator(getMtEngine()) * 0.5;
						helperComponent->playerPosition = LevelManagerHelperComponent::Left;
					} else{
						helperComponent->jumpStartX = 8.5;
						helperComponent->jumpDestX = 0.5 + wallWidthGenerator(getMtEngine()) * 0.5;
						helperComponent->playerPosition = LevelManagerHelperComponent::Right;
					}
				}
				//Increase score by one
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
			break;
		}
	}

	for (Entity* entity : engine.getEntities()){
		if (entity->getComponent<PlayerComponent>() && entity->getComponent<TransformComponent>()->position.y > engine.getLogicalScreenSize().y){
			PlayerSystem::onPlayerDeath(entity);
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