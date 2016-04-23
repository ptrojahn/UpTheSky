#include "LevelManager.h"

#include "TransformComponent.h"
#include "Layer.h"
#include "RenderComponent.h"
#include "Scroll.h"
#include "StaticColliderComponent.h"

void LevelManagerSystem::update(LayersEngine& engine) {
	//Add new entities
	for (Entity* entity : engine.getEntities()){
		if (entity->getComponent<LevelManagerHelperComponent>()){
			float& distance = entity->getComponent<TransformComponent>()->position.y;
			if (distance > 10){
				distance = 0;
				getLayer()->addEntity((new Entity(200))
					->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), 
					                                   BufferManager::instance().createBuffer(BufferManager::rectangleVertices2D(0, 0, 4, 5))))
					->addComponent(new TransformComponent(Vector2<float>(0.5, -5)))
					->addComponent(new StaticColliderComponent(Vector2<float>(4, 5)))
					->addComponent(new ScrollComponent()));
				getLayer()->addEntity((new Entity(200))
					->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
					BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
					->addComponent(new TransformComponent(Vector2<float>(0.5, -5.25)))
					->addComponent(new ScrollComponent())
					->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25))));
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