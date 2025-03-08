// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "CEntitySystem.h"

//------------------------------------------------------------------
// Each Component type will have its own Component Array
// It's a 'Packed' Array:
// - There are no empty positions: Quick iteration, avoids IsValid() checks
// - When an entity is deleted, its component data will still be in its component
//   arrays, but pointing to no entity. And that position should be available 
//   for future entities
//------------------------------------------------------------------

// When an Entity is destroyed we need to update the maps of all Component Arrays
// Added an interface to call them all from ComponentManager
// Improvement: Use custom events, or some other system to avoid inheritance overhead
//------------------------------------------------------------------
struct IComponentArray
{
	virtual ~IComponentArray() = default;
	virtual void OnEntityDestroyed(EntityId entityId) = 0;
};

//------------------------------------------------------------------
template<typename T>
class CComponentArray : public IComponentArray
{
public:
	// IComponentArray
	virtual void OnEntityDestroyed(EntityId entityId) override;
	//~IComponentArray

	void AddEntityData(EntityId entityId, T component);
	void RemoveEntityData(EntityId entityId);
	T& GetComponent(EntityId entityId);

private:
	// To identify positions in the packed array, we map EntityIds (index in the EntitySystem array)
	// to their index in the component array
	std::unordered_map<EntityId, size_t> m_entityIdToIndexMap;

	// We also map it the other way around, to get the EntityId of an index in the component array
	std::unordered_map<size_t, EntityId> m_indexToEntityIdMap;
	
	// The packed array of components of this type (max. 1 component per entity)
	std::array<T, MAX_ENTITIES> m_componentArray;

	// Track how many valid Entities have their component in the component array
	// Used to find last used entry in array
	size_t m_totalEntries{ 0 };
};

// CEntitySystem manages entities
// CComponentManager manages components
//------------------------------------------------------------------
class CComponentManager
{

};