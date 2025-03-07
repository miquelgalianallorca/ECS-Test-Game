// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

struct IComponent;

typedef std::function<std::shared_ptr<IComponent>(const std::string&)> TComponentLoadingFunctor;

//------------------------------------------------------------------
class CComponentManager
{
public:
	// Register all component loading functions
	void Init();

	// All components must be registered with their static function for resolving a Json
	void RegisterComponentLoadingFunction(const std::string& componentName, const TComponentLoadingFunctor&& function);

	// Create a component from Json data
	std::shared_ptr<IComponent> LoadComponentFromJson(const std::string& componentName, const std::string& json);

private:
	// Map of [componentName, loadingFunction] used to create a component from Json data
	std::unordered_map<std::string, TComponentLoadingFunctor> m_componentLoadingFunctions;
};