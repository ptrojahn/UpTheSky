#include "GhostWall.h"

#include "Player.h"
#include "helper.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "StaticColliderComponent.h"
#include "UniformsComponent.h"

void GhostWallSystem::update(LayersEngine& engine) {
	for (Entity* playerEntity : engine.getEntities()){
		if (playerEntity->getComponent<PlayerComponent>()){
			for (Entity* entity : engine.getEntities()){
				GhostWallComponent* ghostComponent = entity->getComponent<GhostWallComponent>();
				if (ghostComponent){
					if (!ghostComponent->initialized){
						entity->addComponent(new UniformsComponent({ Uniform("isGhost", true) }));
						ghostComponent->initialized = true;
					}
					if (ghostComponent->state == GhostWallComponent::Ghost){
						TransformComponent* playerTransComp = playerEntity->getComponent<TransformComponent>();
						TransformComponent* entityTransComp = entity->getComponent<TransformComponent>();
						if (intersect(playerTransComp->position, playerTransComp->scale * PlayerSystem::playerSize, entityTransComp->position, entityTransComp->scale * ghostComponent->triggerSize)){
							ghostComponent->state = GhostWallComponent::Intersecting;
						}
					} else if (ghostComponent->state == GhostWallComponent::Intersecting){
						TransformComponent* playerTransComp = playerEntity->getComponent<TransformComponent>();
						TransformComponent* entityTransComp = entity->getComponent<TransformComponent>();
						if (!intersect(playerTransComp->position, playerTransComp->scale * PlayerSystem::playerSize, entityTransComp->position, entityTransComp->scale * ghostComponent->triggerSize)){
							ghostComponent->state = GhostWallComponent::Solid;
							entity->addComponent(new StaticColliderComponent(ghostComponent->triggerSize));
							*(bool*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0] = false;
						}
					}
				}
			}
		}
	}
}