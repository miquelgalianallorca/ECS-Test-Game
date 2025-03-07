// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentManager.h"
#include "CComponentCollider.h"
#include "CComponentRenderable.h"
#include "CComponentTransform.h"

#include "IComponent.h"

#include <assert.h>

//------------------------------------------------------------------
void CComponentManager::Init()
{
	RegisterComponentLoadingFunction("transform", [](const std::string& data){ return CComponentTransform::LoadComponentFromJson(data); });
	RegisterComponentLoadingFunction("collider", [](const std::string& data){ return CComponentCollider::LoadComponentFromJson(data); });
	RegisterComponentLoadingFunction("renderable", [](const std::string& data){ return CComponentRenderable::LoadComponentFromJson(data); });
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