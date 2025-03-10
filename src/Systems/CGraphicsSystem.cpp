// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CGraphicsSystem.h"

#include "CGame.h"
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
	SetTargetFPS(60);
}

//------------------------------------------------------------------
void CGraphicsSystem::Update(const float& deltaTime)
{
	// Start OpenGL pipeline
	BeginDrawing();
	ClearBackground(BLACK);

	// Test
	ball_x += ball_speed_x;
	ball_y += ball_speed_y;
	if (ball_x + ball_radius >= SCREEN_WIDTH || ball_x - ball_radius <= 0)
	{
		ball_speed_x *= -1;
	}
	if (ball_y + ball_radius >= SCREEN_HEIGHT || ball_y - ball_radius <= 0)
	{
		ball_speed_y *= -1;
	}

	DrawCircle(ball_x, ball_y, ball_radius, WHITE);
	//~Test

	// End OpenGL pipeline
	EndDrawing();
}