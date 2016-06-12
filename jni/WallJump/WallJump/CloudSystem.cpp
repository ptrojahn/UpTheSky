#include "CloudSystem.h"

#include "CloudComponent.h"
#include "BackgroundLayer.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "UniformsComponent.h"
#include "TextureComponent.h"
#include "ScrollComponent.h"

#include <random>

void CloudSystem::update(LayersEngine& engine) {
	if (spawnTime < SDL_GetTicks()){
		std::random_device device;
		std::mt19937 mtEngine(device());
		std::uniform_int_distribution<uint32_t> spawnTimeGenerator(20000, 22000);
		spawnTime = SDL_GetTicks() + spawnTimeGenerator(mtEngine);
		std::uniform_real_distribution<float> yPosGenerator(0, 14);
		std::uniform_int_distribution<int> indexGenerator(0, 3);
		engine.getLayer<BackgroundLayer>()->addEntity((new Entity(300))
			->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "cloud.frag"),
			BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0, 0, 8, 1.0625))))
			->addComponent(new TransformComponent(Vector2<float>(-8.f, yPosGenerator(mtEngine))))
			->addComponent(new UniformsComponent({ Uniform("index", indexGenerator(mtEngine)) }))
			->addComponent(new TextureComponent("clouds.bmp"))
			->addComponent(new CloudComponent(0.2f)));
	}

	for (std::vector<Entity*>::iterator iterEntities = engine.getEntities().begin(); iterEntities != engine.getEntities().end();){
		CloudComponent* cloudComponent = (*iterEntities)->getComponent<CloudComponent>();
		if (cloudComponent){
			float& xPos = (*iterEntities)->getComponent<TransformComponent>()->position.x;
			xPos += cloudComponent->velocity * engine.getDeltaTime();
			if (xPos > 9)
				iterEntities = (*iterEntities)->getLayer()->deleteEntity(*iterEntities);
			else
				iterEntities++;
		} else
			iterEntities++;
	}
}