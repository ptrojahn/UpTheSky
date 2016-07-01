#include "ColorChooserSystem.h"

#include "ColorChooserComponent.h"
#include "UniformsComponent.h"

void ColorChooserSystem::update(LayersEngine& engine) {
	for (Entity* player : engine.getEntities()){
		for (Entity* entity : engine.getEntities()){
			ColorChooserComponent* component = entity->getComponent<ColorChooserComponent>();
			if (component){
				*component->colorOffset = *(float*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0]*-2 + 0.5f;
				*(float*)&entity->getComponent<UniformsComponent>()->uniforms[2].data[0] = 1 - std::min(std::max(*component->skinOffset + component->edge, 0.f), 1.f);
			}
		}
		break;
	}
}