// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#include "CMap.h"
#include "CGame.h"
#include "Components/IComponent.h"
#include "json.hpp"

#include <assert.h> // for assert
#include <iostream> // for std::cout, std::cerr, std::endl
#include <fstream>  // for std::ifstream

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

	CGame& game = CGame::GetInstance();
	CComponentDataLoader& componentDataLoader = game.GetComponentDataLoader();
	CSpriteDataLoader& spriteDataLoader = game.GetSpriteDataLoader();
	CEntityComponentSystem& entityComponentSystem = game.GetEntityComponentSystem();

	// Map has an array of SpriteSheets
	assert(data.contains("spritesheets"));
	assert(data["spritesheets"].is_array());
	for (const auto& spritesheet : data["spritesheets"])
	{
		spriteDataLoader.LoadSpriteSheetFromJson(spritesheet.dump());
	}

	// Map has an array of Entities
	assert(data.contains("entities"));
	assert(data["entities"].is_array());
	for (const auto& entity : data["entities"])
	{
		// Entities must have a name
		assert(entity.contains("name"));
		assert(entity["name"].is_string());
		std::string entityName = entity["name"];

		// Entities must have an array of components
		assert(entity.contains("components"));
		assert(entity["components"].is_array());

		EntityId newEntityId = entityComponentSystem.CreateEntity();
		for (const auto& component : entity["components"])
		{
			assert(component.contains("name"));
			assert(component["name"].is_string());
			const std::string componentName = component["name"];

			// Loads components from json data and adds them to the Entity
			componentDataLoader.LoadComponentFromJson(componentName, component.dump(), newEntityId);
			LogLoadDebug("Loaded ", entityName, componentName);
		}
	}

	iss.close();
	return true;
}

#undef LogLoadDebug
#undef LogLoadError