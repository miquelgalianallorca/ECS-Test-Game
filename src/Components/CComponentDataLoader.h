// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CEntityManager.h" // for EntityId

#include <functional>
#include <string>
#include <unordered_map>

struct IComponent;

typedef std::function<void(const std::string&, EntityId)> TComponentLoadingFunctor;

//------------------------------------------------------------------
class CComponentDataLoader
{
public:
	// Register all component loading functions
	void Init();

	// All components must be registered with their static function for resolving a Json
	void RegisterComponentLoadingFunction(const std::string& componentName, const TComponentLoadingFunctor&& function);

	// Create a component from Json data
	void LoadComponentFromJson(const std::string& componentName, const std::string& json, EntityId entityId);

private:
	// Map of [componentName, loadingFunction] used to create a component from Json data
	std::unordered_map<std::string, TComponentLoadingFunctor> m_componentLoadingFunctions;
};