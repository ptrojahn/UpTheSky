#include "LevelManager.h"

#include "TransformComponent.h"
#include "Layer.h"
#include "RenderComponent.h"
#include "Scroll.h"
#include "StaticColliderComponent.h"
#include "GhostWall.h"
#include "UniformsComponent.h"

void LevelManagerSystem::update(LayersEngine& engine) {
	//Add new entities
	for (Entity* entity : engine.getEntities()){
		if (entity->getComponent<LevelManagerHelperComponent>()){
			float& distance = entity->getComponent<TransformComponent>()->position.y;
			if (distance > 10){
				distance -= 10;
				getLayer()->addEntity((new Entity(200))
					->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometryGhost.frag"), 
					                                   BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 1, 4))))
					->addComponent(new TransformComponent(Vector2<float>(3, -5 + distance)))
					->addComponent(new GhostWallComponent(Vector2<float>(1, 4)))
					->addComponent(new ScrollComponent()));
				break;
			}
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