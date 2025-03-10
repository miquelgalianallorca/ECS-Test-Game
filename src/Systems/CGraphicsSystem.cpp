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

	// End OpenGL pipeline
	EndDrawing();
}