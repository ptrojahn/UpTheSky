#include "PlayerSystem.h"

#include "TransformComponent.h"
#include "StaticColliderComponent.h"
#include "LethalTriggerComponent.h"
#include "PlayerLayer.h"
#include "LevelManagerHelperComponent.h"
#include "ScrollComponent.h"
#include "RenderComponent.h"
#include "GameLayer.h"
#include "MainMenuLayerLogic.h"
#include "Layer.h"
#include "helper.h"
#include "OnWaitFinishedComponent.h"
#include "ParticleComponent.h"
#include "MersenneTwisterEngine.h"
#include "CoinComponent.h"
#include "AnimationComponent.h"
#include "UniformsComponent.h"
#include "TextureComponent.h"
#include "PlayerComponent.h"
#include "SharedPreferences.h"

#include <random>

const Vector2<float> PlayerSystem::playerSize = Vector2<float>(1, 2);
const Vector2<float> PlayerSystem::jumpVelocity = Vector2<float>(8, -13);
const float PlayerSystem::gravity = 25;

int getJumpBlock(std::vector<Entity*> entities, Vector2<float> playerPosition, Vector2<float> playerSize) {
	for (Entity* entity : entities){
		StaticColliderComponent* colliderComponent = entity->getComponent<StaticColliderComponent>();
		if (colliderComponent){
			Vector2<float> colliderPosition = entity->getComponent<TransformComponent>()->position;
			Vector2<float> colliderSize = colliderComponent->size * entity->getComponent<TransformComponent>()->scale;
			if (colliderPosition.x - playerPosition.x - playerSize.x == 0
				&& playerPosition.y + playerSize.y > colliderPosition.y
				&& playerPosition.y < colliderPosition.y + colliderSize.y){
				return 1;
			} else if (playerPosition.x - colliderPosition.x - colliderSize.x == 0
				&& playerPosition.y + playerSize.y > colliderPosition.y
				&& playerPosition.y < colliderPosition.y + colliderSize.y){
				return -1;
			}
		}
	}
	return 0;
}

void deleteTrailEntity(Entity* trailEntity) {
	trailEntity->getLayer()->deleteEntity(trailEntity);
}

void PlayerSystem::update(LayersEngine& engine) {
	for (Entity* playerEntity : engine.getEntities()){
		PlayerComponent* playerComponent = playerEntity->getComponent<PlayerComponent>();
		if (playerComponent){
			TransformComponent* transformComponent = playerEntity->getComponent<TransformComponent>();
			int jumpBlock = getJumpBlock(engine.getEntities(), transformComponent->position, playerSize);
			//Only increase x velocity if the direction is not blocked by a wall. This is needed to avoid glitches on collider corners 
			if (engine.isTouchActive() && !playerComponent->lastFramePressed && jumpBlock){
				if (jumpBlock != copysign(1.0, engine.getTouchPosition().x - engine.getLogicalScreenSize().x / 2))
					playerComponent->velocity.x = copysign(1.0, engine.getTouchPosition().x - engine.getLogicalScreenSize().x / 2) * jumpVelocity.x;
				playerComponent->velocity.y = jumpVelocity.y;
			}
			playerComponent->lastFramePressed = engine.isTouchActive();
			playerComponent->velocity += Vector2<float>(0, gravity * engine.getDeltaTime());

			//Collision handling. The position needs to be set explicitly to avoid float precision problems
			Vector2<float> velocityFactor = Vector2<float>(1, 1);
			Vector2<float> futurePosition = transformComponent->position + playerComponent->velocity * engine.getDeltaTime();
			for (Entity* entity : engine.getEntities()){
				StaticColliderComponent* colliderComponent = entity->getComponent<StaticColliderComponent>();
				if (colliderComponent){
					TransformComponent* colliderTransformComponent = entity->getComponent<TransformComponent>();
					Vector2<float> colliderSize = colliderComponent->size * colliderTransformComponent->scale;
					if (intersect(futurePosition, playerSize, colliderTransformComponent->position, colliderSize)){
						if (transformComponent->position.x + playerSize.x <= colliderTransformComponent->position.x && playerComponent->velocity.x > 0){
							transformComponent->position.x = colliderTransformComponent->position.x - playerSize.x;
							playerComponent->velocity.x = 0;
							velocityFactor.x = 0;
						} else if (transformComponent->position.x >= colliderTransformComponent->position.x + colliderSize.x && playerComponent->velocity.x < 0){
							transformComponent->position.x = colliderTransformComponent->position.x + colliderSize.x;
							playerComponent->velocity.x = 0;
							velocityFactor.x = 0;
						} else if (transformComponent->position.y >= colliderTransformComponent->position.y + colliderComponent->size.y && playerComponent->velocity.y < 0){
							transformComponent->position.y = colliderTransformComponent->position.y + colliderComponent->size.y;
							playerComponent->velocity.y = 0;
							velocityFactor.y = 0;
						} else if (transformComponent->position.y + playerSize.y <= colliderTransformComponent->position.y && playerComponent->velocity.y > 0){
							transformComponent->position.y = colliderTransformComponent->position.y - playerSize.y;
							playerComponent->velocity.y = 0;
							velocityFactor.y = 0;
						}
					}
				}
			}
			transformComponent->position += playerComponent->velocity * velocityFactor * engine.getDeltaTime();

			for (Entity* entity : engine.getEntities()){
				LethalTriggerComponent* triggerComponent = entity->getComponent<LethalTriggerComponent>();
				if (triggerComponent){
					TransformComponent* triggerTransformComponent = entity->getComponent<TransformComponent>();
					Vector2<float> triggerSize = triggerComponent->size * triggerTransformComponent->scale;
					if (intersect(transformComponent->position, playerSize, triggerTransformComponent->position, triggerSize)){
						onPlayerDeath(playerEntity);
						break;
					}
				} else if (entity->getComponent<CoinComponent>() && !entity->getComponent<CoinComponent>()->collected){
					if (intersect(transformComponent->position, playerSize, entity->getComponent<TransformComponent>()->position, Vector2<float>(0.5f, 0.5f))){
						entity->getComponent<CoinComponent>()->collected = true;
						SharedPreferences& sharedPrefs = SharedPreferences::getSharedPreferences();
						sharedPrefs.putInt("money", *(int*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0] + sharedPrefs.getInt("money"));
						sharedPrefs.apply();
						entity->addComponent(new AnimationComponent({
							AnimationState({
								AnimationChange((float*)&entity->getComponent<UniformsComponent>()->uniforms[1].data[0], 0, 1)
							}, 0.6)
						}, AnimationComponent::Once));
					}
				}
			}

			//Trail
			if (playerEntity->getComponent<RenderComponent>()->enabled){
				TransformComponent* transformComponent = playerEntity->getComponent<TransformComponent>();
				Entity* trailItem = new Entity(101);
				trailItem->addComponent(new RenderComponent(ShaderManager::instance().createShader("default.vert", "playerTrail.frag"), BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, PlayerSystem::playerSize.x, PlayerSystem::playerSize.y))));
				UniformsComponent* uniformsComponent = new UniformsComponent({ Uniform("alpha", 1.f), playerEntity->getComponent<UniformsComponent>()->uniforms[0] });
				trailItem->addComponent(uniformsComponent);
				trailItem->addComponent(new TransformComponent(transformComponent->position, transformComponent->rotation, transformComponent->scale));
				trailItem->addComponent(new OnWaitFinishedComponent(100, deleteTrailEntity));
				trailItem->addComponent(new ScrollComponent());
				trailItem->addComponent(new AnimationComponent({
					AnimationState({
						AnimationChange((float*)(&uniformsComponent->uniforms[0].data[0]), 1.f, 0.f)
					}, 0.1f)
				}, AnimationComponent::Once));
				trailItem->addComponent(new TextureComponent({Texture("skinColors.bmp", "colors", GL_NEAREST)}));
				playerEntity->getLayer()->addEntity(trailItem);
			}
			break;
		}
	}
}

//One second after the player died. Clean up the game layer for the next game
void onPlayerRemoved(Entity* player) {
	player->getLayer()->getEngine()->getLayer<GameLayer>()->disable();
	player->getLayer()->getEngine()->getLayer<MainMenuLayerLogic>()->enable();

	//Reset game layer
	for (std::vector<Entity*>::iterator entityIter = player->getLayer()->getEngine()->getEntities().begin(); entityIter != player->getLayer()->getEngine()->getEntities().end();){
		if ((*entityIter)->getLayer()->isClass<GameLayer>())
			entityIter = player->getLayer()->deleteEntity((*entityIter));
		else
			entityIter++;
	}
	player->getLayer()->getEngine()->getLayer<GameLayer>()->addEntity((new Entity(400))
		->addComponent(new LevelManagerHelperComponent())
		->addComponent(new TransformComponent(Vector2<float>(0, 2)))
		->addComponent(new ScrollComponent()));

	//Reset the player
	player->getComponent<RenderComponent>()->enabled = true;
	player->addComponent(new PlayerComponent());
	player->addComponent(new ScrollComponent());
	TransformComponent* component = player->getComponent<TransformComponent>();
	component->scale = Vector2<float>(2, 2);
	component->position = Vector2<float>(player->getLayer()->getEngine()->getLogicalScreenSize().x / 2.f - 1.f, player->getLayer()->getEngine()->getLogicalScreenSize().y / 2.f - 2.f);
}

//The player died. Play the death animation
void PlayerSystem::onPlayerDeath(Entity* player) {
	//Particles
	PlayerComponent* playerComponent = player->getComponent<PlayerComponent>();
	TransformComponent* transformComponent = player->getComponent<TransformComponent>();
	float angle = atan2f(playerComponent->velocity.y, playerComponent->velocity.x) + M_PI * 0.5f;
	if (angle < 0)
		angle += 2.f * M_PI;
	float speed = sqrtf(pow(playerComponent->velocity.y, 2) + pow(playerComponent->velocity.x, 2));
	for (int x = 0; x < 2; x++){
		for (int y = 0; y < 4; y++){
			float particleAngle = atan2f(y * 0.5f + 0.25f - 1.f, x * 0.5f + 0.25f - 0.5f) + M_PI * 0.5f;
			if (particleAngle < 0)
				particleAngle += 2.f * M_PI;
			particleAngle -= angle;
			std::uniform_int_distribution<int> particleDistribution(-20, 20);
			particleAngle += particleDistribution(getMtEngine()) / 10.f;
			player->getLayer()->getEngine()->getLayer<GameLayer>()->addEntity((new Entity(100))
				->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "playerParticle.frag"),
				BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(-0.25f, -0.25f, 0.5f, 0.5f))))
				->addComponent(new TransformComponent(transformComponent->position + Vector2<float>(0.5 * x + 0.25f, 0.5 * y + 0.25f)))
				->addComponent(new ParticleComponent(playerComponent->velocity + Vector2<float>(sinf(particleAngle * 0.25f + angle), cosf(particleAngle * 0.25f + angle)) * 4.f, particleAngle * 2.f))
				->addComponent(new TextureComponent({ Texture("playerAtlas.bmp", "atlas", GL_NEAREST), Texture("skinColors.bmp", "colors", GL_NEAREST) }))
				->addComponent(new UniformsComponent({ player->getComponent<UniformsComponent>()->uniforms[0],
				player->getComponent<UniformsComponent>()->uniforms[1],
				player->getComponent<UniformsComponent>()->uniforms[2],
				player->getComponent<UniformsComponent>()->uniforms[3],
				Uniform("uvOffset", x*0.5, y*0.25) })));
		}
	}
	//Make the player invisible and add the OnWaitFinishedComponent
	player->getComponent<RenderComponent>()->enabled = false;
	player->deleteComponent(player->getComponent<PlayerComponent>());
	player->deleteComponent(player->getComponent<ScrollComponent>());
	player->addComponent(new OnWaitFinishedComponent(1000, onPlayerRemoved));
}