// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "Map.h"

#include <raylib.h> // for Drawing on screen (Improvement: Access library via interface)

//------------------------------------------------------------------
bool Map::LoadMap(const char* fileName)
{
	// ...

	return true;
}

//------------------------------------------------------------------
void Map::OnInit()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Larian Test");
	SetTargetFPS(60);

	for (CEntity& entity : m_entities)
	{
		entity.OnInit();
	}
}

//------------------------------------------------------------------
void Map::OnDone()
{
	for (CEntity& entity : m_entities)
	{
		entity.OnDone();
	}
}

//------------------------------------------------------------------
void Map::Update(const float& deltaTime)
{
	for (CEntity& entity : m_entities)
	{
		entity.Update(deltaTime);
	}
}

//------------------------------------------------------------------
void Map::Render(const float& deltaTime)
{
	BeginDrawing();
	ClearBackground(BLACK);

	for (CEntity& entity : m_entities)
	{
		entity.Render(deltaTime);
	}

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

	EndDrawing();
}