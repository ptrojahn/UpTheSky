#pragma once

#include "Component.h"
#include "Vector2.h"
#include "AudioManager.h"

class PlayerComponent : public BaseComponent<PlayerComponent>
{
public:
	PlayerComponent() : lastFramePressed(false), deathSound(AudioManager::instance().loadAudio("death.ogg")) {}
	Vector2<float> velocity;
	bool lastFramePressed;
	AudioAsset deathSound;
};