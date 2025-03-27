// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#pragma once

#include "CEntityManager.h"

#include <assert.h>
#include <memory> // for std::shared_ptr
#include <set>

//------------------------------------------------------------------
// The SystemManager keeps track of all Systems in the game
// and their ComponentMask signatures (Used to find the specific
// Components that the System cares about)
//------------------------------------------------------------------

//------------------------------------------------------------------
class CSystem
{
public:
	// Which Entities this system cares about
	// Used std::set for performance (binary tree allows insert() and
	// erase() without linear searches).
	// Also avoid duplicate searching: Set entries are unique
	std::set<EntityId> m_viewEntityIds;
};

//------------------------------------------------------------------
class CSystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		// Verify there's no System duplicates
		// System's name is the name of the class
		const char* systemName = typeid(T).name();
		assert(m_systems.find(systemName) == m_systems.end());

		std::shared_ptr<T> pSystem = std::make_shared<T>();
		m_systems.insert({ systemName, pSystem });
		return pSystem;
	}

	template<typename T>
	void SetSystemComponentMask(ComponentMask componentMask)
	{
		// Verify the System has been registered beforehand
		const char* systemName = typeid(T).name();
		assert(m_systems.find(systemName) != m_systems.end());

		m_systemComponentMasks.insert({ systemName, componentMask });
	}

	void OnEntityDestroyed(EntityId entityId);

	void OnEntityComponentsChanged(EntityId entityId, ComponentMask entityComponentsMask);

private:
	// ComponentMasks of each system (mapped by system name)
	std::unordered_map<const char*, ComponentMask> m_systemComponentMasks;

	// Pointers to all Systems (mapped by system name)
	std::unordered_map<const char*, std::shared_ptr<CSystem>> m_systems;
};