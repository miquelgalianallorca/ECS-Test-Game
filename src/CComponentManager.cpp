// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentManager.h"
#include "IComponent.h"

#include <assert.h>

//-------------------------------------------------------------------
// Initialize static members
std::unordered_map<std::string, std::function<IComponent*(const std::string&)>> CComponentManager::m_componentLoadingFunctions = {};

//------------------------------------------------------------------
void CComponentManager::RegisterComponentLoadingFunction(const std::string& componentName, const std::function<IComponent*(const std::string&)>& function)
{
	// Don't register the same component more than once
	//const auto itFunctions = m_componentLoadingFunctions.find(componentName);
	//assert(itFunctions == m_componentLoadingFunctions.end());

	//CComponentManager::m_componentLoadingFunctions.emplace(componentName, function);
}

//------------------------------------------------------------------
IComponent* CComponentManager::LoadComponentFromJson(const std::string& componentName, const std::string& json)
{
	return nullptr;
}