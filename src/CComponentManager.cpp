// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentManager.h"
#include "IComponent.h"

#include <assert.h>

//------------------------------------------------------------------
CComponentManager& CComponentManager::GetInstance()
{
	static CComponentManager instance;
	return instance;
}

//------------------------------------------------------------------
void CComponentManager::RegisterComponentLoadingFunction(const std::string& componentName, const TComponentLoadingFunctor&& function)
{
	// Don't register the same component more than once
	const auto itFunctions = m_componentLoadingFunctions.find(componentName);
	assert(itFunctions == m_componentLoadingFunctions.end());

	CComponentManager::m_componentLoadingFunctions.emplace(componentName, std::move(function));
}

//------------------------------------------------------------------
std::shared_ptr<IComponent> CComponentManager::LoadComponentFromJson(const std::string& componentName, const std::string& json)
{
	const auto itFunctions = m_componentLoadingFunctions.find(componentName);
	assert(itFunctions != m_componentLoadingFunctions.end());

	return itFunctions->second(json);
}