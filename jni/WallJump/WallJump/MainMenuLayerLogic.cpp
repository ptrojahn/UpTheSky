#include "MainMenuLayerLogic.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "ButtonSystem.h"
#include "ButtonComponent.h"
#include "TextureComponent.h"
#include "UniformsComponent.h"
#include "ScoreComponent.h"
#include "UniformsComponent.h"
#include "GameLayer.h"
#include "PlayerLayer.h"
#include "PlayerComponent.h"
#include "PlayerSystem.h"
#include "AnimationComponent.h"
#include "ShopLayerLogic.h"
#include "OnWaitFinishedComponent.h"
#include "AudioManager.h"
#include "SharedPreferences.h"

void startGame(Entity* button, float direction) {
	for (Entity* entity : button->getLayer()->getEngine()->getEntities()){
		PlayerComponent* playerComponent = entity->getComponent<PlayerComponent>();
		if (playerComponent){
			playerComponent->velocity = Vector2<float>(PlayerSystem::jumpVelocity.x * direction, PlayerSystem::jumpVelocity.y);

			entity->addComponent(new AnimationComponent({
				AnimationState({ AnimationChange(&entity->getComponent<TransformComponent>()->scale.x, 2.f, 1.f),
				                 AnimationChange(&entity->getComponent<TransformComponent>()->scale.y, 2.f, 1.f),
								 AnimationChange(&entity->getComponent<TransformComponent>()->position.x, 0.5, 1),
								 AnimationChange(&entity->getComponent<TransformComponent>()->position.y, 1, 2)
				},0.25f),
			}, AnimationComponent::Once));
		}
	}
	button->getLayer()->getEngine()->getLayer<GameLayer>()->enable();
	AudioManager::instance().playAudio(dynamic_cast<MainMenuLayerLogic*>(button->getLayer())->getJumpSound());
}

void jumpLeft(Entity* button) {
	button->getLayer()->disable();
	startGame(button, -1);
}

void jumpRight(Entity* button) {
	button->getLayer()->disable();
	startGame(button, 1);
}

void disablePlayer(Entity* player) {
	player->getComponent<RenderComponent>()->enabled = false;
}

void loadShop(Entity* button) {
	button->getLayer()->disable();
	button->getLayer()->getEngine()->getLayer<ShopLayerLogic>()->enable();
	for (Entity* entity : button->getLayer()->getEngine()->getEntities()){
		if (entity->getComponent<PlayerComponent>()){
			entity->addComponent(new OnWaitFinishedComponent(200, disablePlayer));
			entity->addComponent(new AnimationComponent({
				AnimationState({
					AnimationChange(&entity->getComponent<TransformComponent>()->position.y, 6.f, 1.5f)
				}, 0.1f)
			}, AnimationComponent::Once));
		} else if (entity->getComponent<ScoreComponent>()){
			entity->addComponent(new AnimationComponent({
				AnimationState({
					AnimationChange((float*)&entity->getComponent<UniformsComponent>()->uniforms[2].data[0], 1.f, 0.f)
				}, 0.1f)
			}, AnimationComponent::Once));
		}
	}
}

void toggleSound(Entity* button) {
	AudioManager::instance().setMute(!AudioManager::instance().isMute());
	*(bool*)&dynamic_cast<MainMenuLayerLogic*>(button->getLayer())->getGraphicsLayer()->getSoundButton()->getComponent<UniformsComponent>()->uniforms[1].data[0] = AudioManager::instance().isMute();
	SharedPreferences::getSharedPreferences().putBoolean("muted", AudioManager::instance().isMute());
	SharedPreferences::getSharedPreferences().apply();
}

void MainMenuLayerLogic::load() {
	addEntity((new Entity(0))
		->addComponent(new TransformComponent())
		->addComponent(new ButtonComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f, getEngine()->getLogicalScreenSize().y - 2), &jumpLeft)));
	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f, 0)))
		->addComponent(new ButtonComponent(Vector2<float>(getEngine()->getLogicalScreenSize().x / 2.f, getEngine()->getLogicalScreenSize().y - 2), &jumpRight)));

	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(0.2, 13.8)))
		->addComponent(new ButtonComponent(Vector2<float>(2.f, 2.f), &loadShop)));

	AudioManager::instance().setMute(SharedPreferences::getSharedPreferences().getBoolean("muted"));
	addEntity((new Entity(0))
		->addComponent(new TransformComponent(Vector2<float>(2.4, 13.8)))
		->addComponent(new ButtonComponent(Vector2<float>(2.f, 2.f), &toggleSound)));

	addSystem(new ButtonSystem(1));
}