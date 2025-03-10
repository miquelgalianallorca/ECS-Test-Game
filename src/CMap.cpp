// Author: Miquel Galiana Llorca
// Project: Larian Test

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

	CComponentDataLoader& componentDataLoader = CGame::GetInstance().GetComponentDataLoader();
	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();

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

		EntityId newEntityId = entityComponentSystem.CreateEntity();
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
	}

	iss.close();
	return true;
}

#undef LogLoadDebug
#undef LogLoadError