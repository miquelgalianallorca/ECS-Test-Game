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
	// Singleton pattern
	static CComponentManager& GetInstance();
	CComponentManager(const CComponentManager&) = delete;
	CComponentManager(CComponentManager&&) = delete;
	CComponentManager& operator=(const CComponentManager&) = delete;
	CComponentManager& operator=(CComponentManager&&) = delete;

	// every component registration should register itself to the singleton with its static function for resolving a json
	void RegisterComponentLoadingFunction(const std::string& componentName, const TComponentLoadingFunctor&& function);

	std::shared_ptr<IComponent> LoadComponentFromJson(const std::string& componentName, const std::string& json);

private:
	CComponentManager() = default;

	// Map of [componentName, loadingFunction] used to create a component from Json data
	std::unordered_map<std::string, TComponentLoadingFunctor> m_componentLoadingFunctions;
};