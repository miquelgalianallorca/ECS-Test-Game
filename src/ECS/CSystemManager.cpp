// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CSystemManager.h"

#include <assert.h>

//------------------------------------------------------------------
template<typename T>
std::shared_ptr<T> CSystemManager::RegisterSystem()
{
	// Verify there's no System duplicates
	// System's name is the name of the class
	const char* systemName = typeid(T).name();
	assert(m_systems.find(systemName) == m_systems.end());

	std::shared_ptr<T> pSystem = std::make_shared<T>();
	m_systems.insert({ systemName, pSystem });
	return pSystem;
}

//------------------------------------------------------------------
template<typename T>
void CSystemManager::SetSystemComponentMask(ComponentMask componentMask)
{
	// Verify the System has been registered beforehand
	const char* systemName = typeid(T).name();
	assert(m_systems.find(systemName) != m_systems.end());

	m_systemComponentMasks.insert({ systemName, componentMask });
}

//------------------------------------------------------------------
void CSystemManager::OnEntityDestroyed(EntityId entityId)
{
	// When an Entity is destroyed we remove it from every System
	// Because we're using an std::set in the System, no need to verify find()
	for (const auto& pair : m_systems)
	{
		const auto& pSystem = pair.second;
		pSystem->m_viewEntityIds.erase(entityId);
	}
}

//------------------------------------------------------------------
void CSystemManager::OnEntityComponentsChanged(EntityId entityId, ComponentMask entityComponentMask)
{
	// Notify each system that an entity's signature changed
	for (auto const& pair : m_systems)
	{
		const char* systemName = pair.first;
		const std::shared_ptr<CSystem>& pSystem = pair.second;
		const ComponentMask& systemComponentMask = m_systemComponentMasks[systemName];

		// Bitwise operation
		// If the Entity has all the Components the System neds, we add it to the System
		if ((entityComponentMask & systemComponentMask) == systemComponentMask)
		{
			// The System uses std::set, so no need to verify for duplicates
			// If the entity already was in the System view we just update it
			pSystem->m_viewEntityIds.insert(entityId);
			continue;
		}

		// If the Entity no longer has all the needed Components, we remove it from the System
		pSystem->m_viewEntityIds.erase(entityId);
	}
}