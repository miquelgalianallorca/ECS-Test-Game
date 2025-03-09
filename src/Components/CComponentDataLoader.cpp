// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentDataLoader.h"
#include "Components/SComponentCollider.h"
#include "Components/SComponentRenderable.h"
#include "Components/SComponentTransform.h"

#include "Components/IComponent.h"

#include <assert.h>

//------------------------------------------------------------------
void CComponentDataLoader::Init()
{
	RegisterComponentLoadingFunction("transform", [](const std::string& data){ return SComponentTransform::LoadComponentFromJson(data); });
	RegisterComponentLoadingFunction("collider", [](const std::string& data){ return SComponentCollider::LoadComponentFromJson(data); });
	RegisterComponentLoadingFunction("renderable", [](const std::string& data){ return SComponentRenderable::LoadComponentFromJson(data); });
}

//------------------------------------------------------------------
void CComponentDataLoader::RegisterComponentLoadingFunction(const std::string& componentName, const TComponentLoadingFunctor&& function)
{
	// Don't register the same component more than once
	const auto itFunctions = m_componentLoadingFunctions.find(componentName);
	assert(itFunctions == m_componentLoadingFunctions.end());

	CComponentDataLoader::m_componentLoadingFunctions.emplace(componentName, std::move(function));
}

//------------------------------------------------------------------
std::shared_ptr<IComponent> CComponentDataLoader::LoadComponentFromJson(const std::string& componentName, const std::string& json)
{
	const auto itFunctions = m_componentLoadingFunctions.find(componentName);
	assert(itFunctions != m_componentLoadingFunctions.end());

	return itFunctions->second(json);
}