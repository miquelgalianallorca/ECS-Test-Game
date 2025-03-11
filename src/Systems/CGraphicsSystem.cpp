// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CGraphicsSystem.h"

#include "CGame.h"
#include "Components/IShape.h"
#include "Components/SComponentCollider.h"
#include "Components/SComponentRenderable.h"
#include "Components/SComponentTransform.h"
#include "ECS/CEntityComponentSystem.h"

#include <raylib.h> // for Drawing on screen (Improvement: Access library via interface)

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

	// Test
	ball.Update();
	ball.Draw();
	//~Test

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	//entityComponentSystem.SComponentCollider

	for (const EntityId entityId : m_viewEntityIds)
	{
		SComponentTransform& transform = entityComponentSystem.GetComponent<SComponentTransform>(entityId);
		SComponentRenderable& renderable = entityComponentSystem.GetComponent<SComponentRenderable>(entityId);
		SComponentCollider& collider = entityComponentSystem.GetComponent<SComponentCollider>(entityId);

		std::shared_ptr<IShape> pShape = renderable.m_pShape;
		//pShape->Draw(posX, posY, color);

		Color color;
		color.r = renderable.m_color[0];
		color.g = renderable.m_color[1];
		color.b = renderable.m_color[2];
		color.a = renderable.m_color[3];
		DrawCircle(transform.m_posX, transform.m_posY, 50.f/*radius*/, color);
	}

	// End OpenGL pipeline
	EndDrawing();
}