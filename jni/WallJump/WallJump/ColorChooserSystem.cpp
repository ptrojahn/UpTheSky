#include "ColorChooserSystem.h"

#include "ColorChooserComponent.h"
#include "UniformsComponent.h"

void ColorChooserSystem::update(LayersEngine& engine) {
	for (Entity* player : engine.getEntities()){
		for (Entity* entity : engine.getEntities()){
			ColorChooserComponent* component = entity->getComponent<ColorChooserComponent>();
			if (component){
				*component->offsetPointer = *(float*)&entity->getComponent<UniformsComponent>()->uniforms[0].data[0]*-2 + 0.5f;
			}
		}
		break;
	}
}