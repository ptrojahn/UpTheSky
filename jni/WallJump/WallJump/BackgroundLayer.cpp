#include "BackgroundLayer.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "ShaderManager.h"
#include "BufferManager.h"
#include "TransformComponent.h"
#include "UniformsComponent.h"
#include "ScrollComponent.h"
#include "TextureComponent.h"

void BackgroundLayer::load() {
	addEntity((new Entity(300))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 4.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 13.5f)))
		->addComponent(new UniformsComponent({Uniform("color", 0.2f, 1.f, 0.2f)}))
		->addComponent(new ScrollComponent(0.1f))
		->addComponent(new TextureComponent("hills1.bmp")));
	addEntity((new Entity(301))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 4.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 12.f)))
		->addComponent(new UniformsComponent({ Uniform("color", 0.4f, 1.f, 0.4f) }))
		->addComponent(new ScrollComponent(0.08f))
		->addComponent(new TextureComponent("hills2.bmp")));
	addEntity((new Entity(302))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 4.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 10.5f)))
		->addComponent(new UniformsComponent({ Uniform("color", 0.6f, 1.f, 0.6f) }))
		->addComponent(new ScrollComponent(0.06f))
		->addComponent(new TextureComponent("hills3.bmp")));
	addEntity((new Entity(303))
		->addComponent(new RenderComponent(ShaderManager::instance().createShader("defaultUV.vert", "backgroundHeightMap.frag"),
		BufferManager::instance().createBuffer(BufferManager::rectangleVertices2DUV(0.f, 0.f, 9.f, 4.f))))
		->addComponent(new TransformComponent(Vector2<float>(0.f, 9.f)))
		->addComponent(new UniformsComponent({ Uniform("color", 0.7f, 0.7f, 0.7f) }))
		->addComponent(new ScrollComponent(0.04f))
		->addComponent(new TextureComponent("hills4.bmp")));

	addSystem(new RenderSystem(0));
}