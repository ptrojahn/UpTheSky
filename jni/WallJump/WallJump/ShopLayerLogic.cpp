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
#include "UniformsComponent.h"
#include "SharedPreferences.h"

void lockWiggle(Entity* entity) {
	Vector2<float>& position = entity->getComponent<TransformComponent>()->position;
	entity->addComponent(new AnimationComponent({
		AnimationState({ AnimationChange(&position.x, 0, 0.2) }, 0.01),
		AnimationState({ AnimationChange(&position.x, 0.2, -0.2) }, 0.1),
		AnimationState({ AnimationChange(&position.x, -0.2, 0.2) }, 0.1),
		AnimationState({ AnimationChange(&position.x, 0.2, 0) }, 0.05)
	}, AnimationComponent::Once));
}

void loadMenu(Entity* button) {
	Entity* lock = dynamic_cast<ShopLayerLogic*>(button->getLayer())->getGraphicsLayer()->getLock();
	if (*(float*)&lock->getComponent<UniformsComponent>()->uniforms[1].data[0] > 0.5){
		lockWiggle(lock);
	} else{
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
	AudioManager::instance().playAudio(dynamic_cast<ShopLayerLogic*>(button->getLayer())->getUiInteractionSound());
}

void buySkin(Entity* entity) {
	ShopLayerGraphics* graphicsLayer = dynamic_cast<ShopLayerLogic*>(entity->getLayer())->getGraphicsLayer();
	if (*(float*)&graphicsLayer->getLock()->getComponent<UniformsComponent>()->uniforms[1].data[0] > 0.5){
		int money = SharedPreferences::getSharedPreferences().getInt("money");
		int price = *(int*)&graphicsLayer->getSkinPrice()->getComponent<UniformsComponent>()->uniforms[2].data[0];
		if (money > price){
			SharedPreferences::getSharedPreferences().putInt("money", money - price);
			int skinIndex = *(float*)&graphicsLayer->getSkinChooser()->getComponent<UniformsComponent>()->uniforms[1].data[0] / -2.f;
			SharedPreferences::getSharedPreferences().putInt(("skinUnlocked" + std::to_string(skinIndex)).c_str(), 1);
			SharedPreferences::getSharedPreferences().apply();
			AudioManager::instance().playAudio(dynamic_cast<ShopLayerLogic*>(entity->getLayer())->getBuySkinSound());
		} else {
			lockWiggle(graphicsLayer->getLock());
			AudioManager::instance().playAudio(dynamic_cast<ShopLayerLogic*>(entity->getLayer())->getUiInteractionSound());
		}
	}
}

void ShopLayerLogic::load() {
	uiInteractionSound = AudioManager::instance().loadAudio("uiInteraction.ogg");
	buySkinSound = AudioManager::instance().loadAudio("collectCoin.ogg");

	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8)))
		->addComponent(new ButtonComponent(Vector2<float>(2.f, 2.f), &loadMenu)));
	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(3.5f, 1.5f)))
		->addComponent(new ButtonComponent(Vector2<float>(2.f, 4.f), &buySkin)));

	addSystem(new HorizontalScrollSystem(2));
	addSystem(new ButtonSystem(1));
	SharedPreferences::getSharedPreferences().putInt("skinUnlocked0", 1);
	SharedPreferences::getSharedPreferences().apply();
}