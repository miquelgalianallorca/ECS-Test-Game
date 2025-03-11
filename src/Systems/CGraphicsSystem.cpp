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
	for (const EntityId entityId : m_viewEntityIds)
	{
		SComponentTransform& transform = entityComponentSystem.GetComponent<SComponentTransform>(entityId);
		SComponentRenderable& renderable = entityComponentSystem.GetComponent<SComponentRenderable>(entityId);
		SComponentCollider& collider = entityComponentSystem.GetComponent<SComponentCollider>(entityId);

		// If the entity is moving, use velocity to guess the drawing position
		float drawPosX = transform.m_posX; // + collider.m_velocityX * deltaTime;
		float drawPosY = transform.m_posY; // + collider.m_velocityY * deltaTime;

		Color color;
		color.r = renderable.m_color[0];
		color.g = renderable.m_color[1];
		color.b = renderable.m_color[2];
		color.a = renderable.m_color[3];

		// Interpolation: Draw at a point between the last state and the current state
		// What we draw will always be a tiny bit behind the current state
		//const double alpha = accumulator / dt; // acumulator (value between 0 and dt)
		//State state = currentState * alpha + previousState * ( 1.0 - alpha );

		// TO DO: Draw should be on the shapes (They use different methods)
		std::shared_ptr<IShape> pShape = renderable.m_pShape;
		//pShape->Draw(posX, posY, color);
		DrawCircle(drawPosX, drawPosY, 50.f/*radius*/, color);

		
		renderable.m_lastDrawPosX = drawPosX;
		renderable.m_lastDrawPosY = drawPosY;
	}

	// End OpenGL pipeline
	EndDrawing();
}