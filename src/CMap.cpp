// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CMap.h"
#include "CGame.h"
#include "IComponent.h"
#include "json.hpp"

#include <assert.h> // for assert
#include <iostream>
#include <fstream>  // for std::ifstream
#include <raylib.h> // for Drawing on screen (Improvement: Access library via interface)

#define LogLoadDebug(str, entityName, componentName) std::cout << str << " - Component: " << componentName << ", Entity: " << entityName << std::endl
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

	CComponentDataLoader& componentDataLoader = CGame::GetInstance().GetComponentDataLoader();
	CEntityManager& entityManager = CGame::GetInstance().GetEntityManager();

	// Map is an array of entities
	for (const auto& entity : data)
	{
		// Entities must have a name
		assert(entity.contains("name"));
		assert(entity["name"].is_string());
		std::string entityName = entity["name"];

		// Entities must have an array of components
		assert(entity.contains("components"));
		assert(entity["components"].is_array());

		EntityId newEntityId = entityManager.CreateEntity();
		for (const auto& component : entity["components"])
		{
			assert(component.contains("name"));
			assert(component["name"].is_string());
			const std::string componentName = component["name"];

			// TO DO: send newEntityId to these loading functions
			// so that the component is registered to the entity via
			//componentManager.AddComponent<ComponentType>(entityId);
			std::shared_ptr<IComponent> pComponent = componentDataLoader.LoadComponentFromJson(componentName, component.dump());
			if (!pComponent)
			{
				LogLoadError("Failed to load Component", entityName, componentName);
				continue;
			}

			LogLoadDebug("Loaded ", entityName, componentName);
		}

		//m_entities.emplace_back(std::move(newEntity));
	}

	iss.close();
	return true;
}

//------------------------------------------------------------------
void CMap::OnInit()
{
	// TO DO: Move to graphics system
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Larian Test");
	SetTargetFPS(60);
}

//------------------------------------------------------------------
void CMap::OnDone()
{
}

//------------------------------------------------------------------
void CMap::Update(const float& deltaTime)
{
}

//------------------------------------------------------------------
void CMap::Render(const float& deltaTime)
{
	// TO DO: Move to graphics system
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

	EndDrawing();
}

#undef LogLoadDebug
#undef LogLoadError