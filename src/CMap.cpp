// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CMap.h"
#include "CGame.h"
#include "CEntity.h"
#include "IComponent.h"
#include "json.hpp"

#include <assert.h> // for assert
#include <iostream>
#include <fstream>  // for std::ifstream
#include <raylib.h> // for Drawing on screen (Improvement: Access library via interface)

#define LogLoadDebug(str, entityName) std::cout << str << " - Entity: " << entityName << std::endl
#define LogLoadError(str, entityName, componentName) std::cerr << str << " - Component: " << componentName << ", Entity: " << entityName << std::endl

using json = nlohmann::json;

//------------------------------------------------------------------
bool CMap::LoadMap(const char* fileName)
{
	std::ifstream iss(fileName);
	json data = json::parse(iss);
	if (data.empty())
	{
		return false;
	}

	CComponentManager& componentManager = CGame::GetInstance().GetComponentManager();

	// Map is an array of entities
	EntityId entityIndex = 0;
	for (const auto& entity : data)
	{
		// Entities must have a name
		assert(entity.contains("name"));
		assert(entity["name"].is_string());
		std::string entityName = entity["name"];

		// Entities must have an array of components
		assert(entity.contains("components"));
		assert(entity["components"].is_array());

		CEntity newEntity(++entityIndex, std::move(entityName));
		for (const auto& component : entity["components"])
		{
			assert(component.contains("name"));
			assert(component["name"].is_string());
			const std::string componentName = component["name"];

			std::shared_ptr<IComponent> pComponent = componentManager.LoadComponentFromJson(componentName, component.dump());
			if (!pComponent)
			{
				LogLoadError("Failed to load Component", newEntity.GetName(), componentName);
				continue;
			}

			newEntity.AddComponent(pComponent);
			LogLoadDebug("Component loaded", newEntity.GetName());

			/*
			else if (className == "actor")
			{
				// health, speed
				// skills?
				// isPlayer? (only one party NPC starts as player)
				// isPartyNPC? (add to UI on entity created)
				// isEnemy? (add to AI on entity created)
				// ...
			}
			else if (className == "effect")
			{
				// other stuff (water, fire)
				// damage over time
				// movement slowing
				// instant death
				// ...
			}
			else if (className == "gamerules")
			{
				// victory conditions?
				// getting somewhere? time limit? kill X enemies?
				// ...
			}
			*/
		}

		m_entities.emplace_back(std::move(newEntity));
	}

	iss.close();
	return true;
}

//------------------------------------------------------------------
void CMap::OnInit()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Larian Test");
	SetTargetFPS(60);

	for (CEntity& entity : m_entities)
	{
		entity.OnInit();
	}
}

//------------------------------------------------------------------
void CMap::OnDone()
{
	for (CEntity& entity : m_entities)
	{
		entity.OnDone();
	}
}

//------------------------------------------------------------------
void CMap::Update(const float& deltaTime)
{
	for (CEntity& entity : m_entities)
	{
		entity.Update(deltaTime);
	}
}

//------------------------------------------------------------------
void CMap::Render(const float& deltaTime)
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

#undef LogLoadDebug
#undef LogLoadError