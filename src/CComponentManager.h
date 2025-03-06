// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <functional>
#include <string>
#include <unordered_map>

struct IComponent;

//------------------------------------------------------------------
// make this component manager a singleton
class CComponentManager
{
public:

	// every component registration should register itself to the singleton with its static function for resolving a json
	static void RegisterComponentLoadingFunction(const std::string& componentName, const std::function<IComponent*(const std::string&)>& function);

	static IComponent* LoadComponentFromJson(const std::string& componentName, const std::string& json);

//private:
	// Map of [componentName, loadingFunction] used to create a component from Json data
	static std::unordered_map<std::string, std::function<IComponent*(const std::string&)>> m_componentLoadingFunctions;
};