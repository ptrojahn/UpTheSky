#include "HorizontalScrollSystem.h"

#include "HorizontalScrollComponent.h"
#include "TransformComponent.h"

#include <algorithm>

namespace{
	bool pressed = false;
	float lastPosition;
}

void HorizontalScrollSystem::update(LayersEngine& engine) {
	for (Entity* entity : engine.getEntities()){
		HorizontalScrollComponent* component = entity->getComponent<HorizontalScrollComponent>();
		if (component){
			if (engine.isTouchActive()){
				if (engine.getTouchPosition().x > entity->getComponent<TransformComponent>()->position.x && engine.getTouchPosition().x < entity->getComponent<TransformComponent>()->position.x + component->size.x
					&& engine.getTouchPosition().y > entity->getComponent<TransformComponent>()->position.y && engine.getTouchPosition().y < entity->getComponent<TransformComponent>()->position.y + component->size.y){
					if (!pressed){
						lastPosition = engine.getTouchPosition().x;
						pressed = true;
					} else {
						*component->currentValue = std::max(std::min(*component->currentValue + (engine.getTouchPosition().x - lastPosition), component->maxValue), component->minValue);
						lastPosition = engine.getTouchPosition().x;
					}
				}
			} else {
				pressed = false;
				if (*component->currentValue > floorf(*component->currentValue / component->step) * component->step + component->step / 2.f)
					*component->currentValue = std::min(*component->currentValue + 10.f * engine.getDeltaTime(), ceilf(*component->currentValue / component->step) * component->step);
				else if (*component->currentValue < floorf(*component->currentValue / component->step) * component->step + component->step / 2.f)
					*component->currentValue = std::max(*component->currentValue - 10.f * engine.getDeltaTime(), floorf(*component->currentValue / component->step) * component->step);
			}
		}
	}
}