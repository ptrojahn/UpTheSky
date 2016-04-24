#include "LevelManager.h"

#include "TransformComponent.h"
#include "Layer.h"
#include "RenderComponent.h"
#include "Scroll.h"
#include "StaticColliderComponent.h"
#include "GhostWall.h"
#include "UniformsComponent.h"

int randomId(std::vector<int> ids) {
	return ids[rand() % ids.size()];
}

void LevelManagerSystem::update(LayersEngine& engine) {
	//Add new entities
	for (Entity* entity : engine.getEntities()){
		LevelManagerHelperComponent* helperComponent = entity->getComponent<LevelManagerHelperComponent>();
		if (helperComponent){
			float& distance = entity->getComponent<TransformComponent>()->position.y;
			if (distance > 9){
				distance -= 9;
				//Choose section
				switch (helperComponent->levelSectionId)
				{
				case -1:
					helperComponent->levelSectionId = randomId({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 });
					break;
				case 0:
					helperComponent->levelSectionId = randomId({ 2, 5, 9, 10, 11, 12 });
					break;
				case 1:
					helperComponent->levelSectionId = randomId({ 3, 4, 6, 9, 12, 13 });
					break;
				case 2:
					helperComponent->levelSectionId = randomId({ 4, 5, 6, 9, 10, 11, 12, 0 });
					break;
				case 3:
					helperComponent->levelSectionId = randomId({ 4, 5, 6, 7, 9, 13, 1, 2 });
					break;
				case 4:
					helperComponent->levelSectionId = randomId({ 6, 9, 13, 0, 1, 2});
					break;
				case 5:
					helperComponent->levelSectionId = randomId({ 6, 8, 9, 13, 1, 2, 3, 4});
					break;
				case 6:
					helperComponent->levelSectionId = randomId({7, 8, 9, 10, 11, 12, 13, 0, 1, 2, 3, 4});
					break;
				case 7:
					helperComponent->levelSectionId = randomId({8, 9, 10, 11, 12, 0});
					break;
				case 8:
					helperComponent->levelSectionId = randomId({9, 10, 11, 12, 0, 4, 6, 7});
					break;
				case 9:
					helperComponent->levelSectionId = randomId({6});
					break;
				case 10:
					helperComponent->levelSectionId = randomId({13, 3, 4, 9});
					break;
				case 11:
					helperComponent->levelSectionId = randomId({13, 3, 9});
					break;
				case 12:
					helperComponent->levelSectionId = randomId({13, 2, 3, 4, 6, 7, 8, 9});
					break;
				case 13:
					helperComponent->levelSectionId = randomId({2, 3, 4, 5, 8, 9, 10, 11});
					break;
				default:
					break;
				}

				//Create section
				switch (helperComponent->levelSectionId)
				{
				case 0:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"), 
						                                   BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 4, 6))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -6 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(4, 6)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						                                   BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -6.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_left.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(8.25, -4 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					break;
				case 1:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 2, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -4 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(2, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 3))))
						->addComponent(new TransformComponent(Vector2<float>(1.5, -7 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 3)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 2, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6.5, -5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(2, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 3))))
						->addComponent(new TransformComponent(Vector2<float>(6.5, -8 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 3)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(1.5, -7.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -4.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6.5, -8.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -5.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					break;
				case 2:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 6))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -6 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 6)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 6, 0.5))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -6.5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(6, 0.5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 0.5, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6, -6 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(0.5, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 0.5, 1.5))))
						->addComponent(new TransformComponent(Vector2<float>(6, -1.5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(0.5, 1.5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 2, 0.5))))
						->addComponent(new TransformComponent(Vector2<float>(6.5, -0.5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(2, 0.5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.5, 0.25, 2, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6, -1.75 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.5, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 2, 0.25, 8, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6.5, -0.75 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(2, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 6, 0.25, 24, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -6.75 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(6, 0.25)))
						->addComponent(new ScrollComponent()));
					break;
				case 3:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 4, 6))))
						->addComponent(new TransformComponent(Vector2<float>(5.5, -6 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(4, 6)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
						->addComponent(new TransformComponent(Vector2<float>(5.5, -6.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_right.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -4 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					break;
				case 4:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 2, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(2, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 2, 0.25, 8, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -5.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(2, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 0.5))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -1.5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 0.5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -1.75 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 0.5))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -7.5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 0.5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -7.75 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					break;
				case 5:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(4.5, -8 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(4, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
						->addComponent(new TransformComponent(Vector2<float>(4.5, -8.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometryGhost.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 5))))
						->addComponent(new TransformComponent(Vector2<float>(4.5, -7 + distance)))
						->addComponent(new GhostWallComponent(Vector2<float>(1, 5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_right.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1.5, 1, 6))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -7 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1.5)))
						->addComponent(new ScrollComponent()));
					break;
				case 6:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 2.5, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6, -8 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(2.5, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 2.5, 0.25, 10, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -8.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(2.5, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometryGhost.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 0.5, 2))))
						->addComponent(new TransformComponent(Vector2<float>(6, -7 + distance)))
						->addComponent(new GhostWallComponent(Vector2<float>(0.5, 2)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 2.5, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -8 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(2.5, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 2.5, 0.25, 10, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6, -8.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(2.5, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometryGhost.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 0.5, 4))))
						->addComponent(new TransformComponent(Vector2<float>(2.5, -7 + distance)))
						->addComponent(new GhostWallComponent(Vector2<float>(0.5, 4)))
						->addComponent(new ScrollComponent()));
					break;
				case 7:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -9 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(4, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -9.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 5, 0.5))))
						->addComponent(new TransformComponent(Vector2<float>(5, -2 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(5, 0.5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 3, 0.25, 12, 1))))
						->addComponent(new TransformComponent(Vector2<float>(5, -2.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(3, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 5))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -7 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -7.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					break;
				case 8:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 5))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -8 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 5)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -8.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 2))))
						->addComponent(new TransformComponent(Vector2<float>(1.5, -5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 2)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(1.5, -5.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 6))))
						->addComponent(new TransformComponent(Vector2<float>(7.5, -7 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 6)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 2))))
						->addComponent(new TransformComponent(Vector2<float>(6.5, -7 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 2)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 2, 0.25, 8, 1))))
						->addComponent(new TransformComponent(Vector2<float>(6.5, -7.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(2, 0.25)))
						->addComponent(new ScrollComponent()));
					break;
				case 9:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometryGhost.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 3, 3))))
						->addComponent(new TransformComponent(Vector2<float>(3, -6 + distance)))
						->addComponent(new GhostWallComponent(Vector2<float>(3, 3)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_right.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -6 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_left.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(8.25, -6 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					break;
				case 10:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometryGhost.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 3))))
						->addComponent(new TransformComponent(Vector2<float>(4, -6 + distance)))
						->addComponent(new GhostWallComponent(Vector2<float>(1, 3)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_right.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 2, 1, 8))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -2 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 2)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_right.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -7 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_left.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(8.25, -7 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					break;
				case 11:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 2))))
						->addComponent(new TransformComponent(Vector2<float>(3, -3 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 2)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(3, -3.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_right.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -2 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 1, 2))))
						->addComponent(new TransformComponent(Vector2<float>(5, -8.5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(1, 2)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 1, 0.25, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(5, -8.75 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(1, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_left.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(8.25, -7.5 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					break;
				case 12:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(4.5, -8.5 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(4, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
						->addComponent(new TransformComponent(Vector2<float>(4.5, -8.75 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -1 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(4, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -1.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
						->addComponent(new ScrollComponent()));
					break;
				case 13:
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("levelGeometry.vert", "levelGeometry.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2D(0, 0, 4, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -8 + distance)))
						->addComponent(new StaticColliderComponent(Vector2<float>(4, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_up.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 4, 0.25, 16, 1))))
						->addComponent(new TransformComponent(Vector2<float>(0.5, -8.25 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(4, 0.25)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_left.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(8.25, -8.5 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					getLayer()->addEntity((new Entity(200))
						->addComponent(new RenderComponent(ShaderManager::instance().createShader("spikes.vert", "spikes_left.frag"),
						BufferManager::instance().createBuffer(BufferManager::instance().rectangleVertices2DUV(0, 0, 0.25, 1, 1, 4))))
						->addComponent(new TransformComponent(Vector2<float>(8.25, -1.5 + distance)))
						->addComponent(new LethalTriggerComponent(Vector2<float>(0.25, 1)))
						->addComponent(new ScrollComponent()));
					break;
				default:
					break;
				}

			}
			break;
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