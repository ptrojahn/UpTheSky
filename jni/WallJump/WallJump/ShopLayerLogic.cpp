#include "ShopLayerLogic.h"

#include "ButtonSystem.h"
#include "TransformComponent.h"
#include "ButtonComponent.h"
#include "MainMenuLayerLogic.h"
#include "PlayerComponent.h"
#include "AnimationComponent.h"
#include "UniformsComponent.h"
#include "ScoreComponent.h"
#include "HorizontalScrollSystem.h"
#include "OnWaitFinishedComponent.h"
#include "RenderComponent.h"

void loadMenu(Entity* button) {
	button->getLayer()->disable();
	button->getLayer()->getEngine()->getLayer<MainMenuLayerLogic>()->enable();
	for (Entity* entity : button->getLayer()->getEngine()->getEntities()){
		if (entity->getComponent<PlayerComponent>()){
			entity->getComponent<RenderComponent>()->enabled = true;
			entity->deleteComponent(entity->getComponent<OnWaitFinishedComponent>());
			entity->addComponent(new AnimationComponent({
				AnimationState({
					AnimationChange(&entity->getComponent<TransformComponent>()->position.y, 1.5f, 1.5f)
				}, 0.1f),
				AnimationState({
					AnimationChange(&entity->getComponent<TransformComponent>()->position.y, 1.5f, 6.f)
				}, 0.1f)
			}, AnimationComponent::Once));
		} else if (entity->getComponent<ScoreComponent>()){
			entity->addComponent(new AnimationComponent({
				AnimationState({
					AnimationChange((float*)&entity->getComponent<UniformsComponent>()->uniforms[2].data[0], 0.f, 1.f)
				}, 0.1f)
			}, AnimationComponent::Once));
		}
	}
}

void ShopLayerLogic::load() {
	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8)))
		->addComponent(new ButtonComponent(Vector2<float>(2.f, 2.f), &loadMenu)));

	addSystem(new HorizontalScrollSystem(2));
	addSystem(new ButtonSystem(1));
}