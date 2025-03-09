// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "CEntityManager.h"

#include <memory> // for std::shared_ptr
#include <set>    // for std::set

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
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSystemComponentMask(ComponentMask componentMask);

	void OnEntityDestroyed(EntityId entityId);

	void OnEntityComponentsChanged(EntityId entityId, ComponentMask entityComponentsMask);

private:
	// ComponentMasks of each system (mapped by system name)
	std::unordered_map<const char*, ComponentMask> m_systemComponentMasks;

	// Pointers to all Systems (mapped by system name)
	std::unordered_map<const char*, std::shared_ptr<CSystem>> m_systems;
};