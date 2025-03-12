// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CGraphicsSystem.h"

#include "CGame.h"
#include "Components/IShape.h"
#include "Components/SComponentCollider.h"
#include "Components/SComponentRenderable.h"
#include "Components/SComponentTransform.h"
#include "ECS/CEntityComponentSystem.h"

#include <iostream> // for std::cout
#include <raylib.h>

//------------------------------------------------------------------
void CGraphicsSystem::Init()
{
	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();

	ComponentMask graphicsSystemComponentMask;
	graphicsSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentTransform>());
	graphicsSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentRenderable>());
	graphicsSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentCollider>());
	
	entityComponentSystem.SetSystemComponentMask<CGraphicsSystem>(graphicsSystemComponentMask);

	// Raylib
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Larian Test");
	SetTargetFPS(120);
}

//------------------------------------------------------------------
void CGraphicsSystem::Update(const float& deltaTime)
{
	// Start OpenGL pipeline
	BeginDrawing();
	ClearBackground(BLACK);

	Time currentTime = std::chrono::high_resolution_clock::now();

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	for (const EntityId entityId : m_viewEntityIds)
	{
		SComponentTransform& transform = entityComponentSystem.GetComponent<SComponentTransform>(entityId);
		SComponentRenderable& renderable = entityComponentSystem.GetComponent<SComponentRenderable>(entityId);
		SComponentCollider& collider = entityComponentSystem.GetComponent<SComponentCollider>(entityId);

		// Interpolation: Draw at a point between the last state and the current state
		// We will always "draw the past" for a little margin, getting the right midpoint between the last
		// change and the previous one
		const float timeSinceUpdate = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - transform.m_lastUpdateTime).count();
		const float alpha = timeSinceUpdate / UPDATE_TIME;

		float drawPosX = (transform.m_posX * alpha) + (transform.m_lastPosX * (1.f - alpha));
		float drawPosY = (transform.m_posY * alpha) + (transform.m_lastPosY * (1.f - alpha));

		std::shared_ptr<IShape> pShape = renderable.m_pShape;
		assert(pShape);
		pShape->Draw(drawPosX, drawPosY, renderable.m_color);
	}

	// End OpenGL pipeline
	EndDrawing();
}