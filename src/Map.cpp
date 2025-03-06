// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "Map.h"
#include "CEntity.h"
#include "json.hpp"

#include <assert.h> // for assert
#include <iostream>
#include <fstream>  // for std::ifstream
#include <raylib.h> // for Drawing on screen (Improvement: Access library via interface)

using json = nlohmann::json;

//------------------------------------------------------------------
bool Map::LoadMap(const char* fileName)
{
	std::ifstream iss(fileName);

	 // Variable to store each line from the file
	// std::string line;
	 // Read each line from the file and print it
	// while (std::getline(iss, line))
	// {
	//		// Process each line as needed
	//		std::cout << line << std::endl;
	 //}


	json data = json::parse(iss);

	// Map is an array of entities
	EntityId entityIndex = 0;
	for (const auto& entity : data)
	{
		// Entities must have a name
		assert(entity.contains("name"));
		assert(entity["name"].is_string());
		std::string entityName = entity["name"];

		// Entities must have a transform (pos, rot)
		assert(entity.contains("pos"));
		assert(entity["pos"].is_array());
		assert(entity["pos"].size() == 2);
		assert(entity["pos"][0].is_number_float());
		assert(entity["pos"][1].is_number_float());

		assert(entity.contains("rot"));
		assert(entity["rot"].is_number_float());
		CEntity::STransform transform
		{
			entity["pos"][0], // pos.x
			entity["pos"][1], // pos.y
			entity["rot"],    // rot
		};

		// Entities must have an array of components
		assert(entity.contains("components"));
		assert(entity["components"].is_array());

		CEntity newEntity(++entityIndex, std::move(entityName), std::move(transform));
		for (const auto& component : entity["components"])
		{
			assert(component.contains("class"));
			assert(component["class"].is_string());
			const std::string className = component["class"];

			// Improvement: Registering components to avoid switch here
			if (className == "collider")
			{
				// pos, rot
				// size?
				// isBlocking (allows moving through)
				// mass (-1 immovable)
				// ...
			}
			else if (className == "shape")
			{
				// renderables - square or circle?
				// pos, rot
				// size? radius?
				// offset (from entity transform)
				// ...
			}
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
			// ...
		}

		m_entities.emplace_back(std::move(newEntity));
	}
	// ...

	iss.close();
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