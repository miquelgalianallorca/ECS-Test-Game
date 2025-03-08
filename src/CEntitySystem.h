// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <array>
#include <bitset>
#include <cstdint> // for std::uint32_t
#include <queue>
#include <unordered_map>
#include <vector>

//------------------------------------------------------------------
// In an Object-Oriented ECS, an Entity would be an Object with components, and each component has logic
// to operate with them.
//
// In a pure ECS an Entity is just an ID associated to a collection of components, it has no logic
// An Entity is just an Id, a Component just data, and a System just has functions
//
// Benefits:
// - Instead of iterating over every Entity, each System can only iterate through the Entities that have
//   the components it cares about, and skip the rest.
// - Some components (ie. Transform) can be used by many Systems, and this avoids jumps in accessing
//   memory between components.
// - Better encapsulation: A change in a Component wouldn't break the logic of every other Component that
//   uses it.
//------------------------------------------------------------------

// Identifies an Entity by being an index to the Entity list
typedef std::uint32_t EntityId;

// Bitmask to check which Components an Entity has
// For a System to check if it has to operate on an Entity, it would just
// need a bitwise operation to compare its signature mask with the Entity's
const int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

// Arbitrary entity limit
const EntityId MAX_ENTITIES = 1024;

//------------------------------------------------------------------
class CEntitySystem
{
public:
	CEntitySystem();

	EntityId CreateEntity();
	void DestroyEntity(EntityId entityId);
	void SetEntityComponentMask(EntityId entityId, ComponentMask componentMask);
	ComponentMask GetEntityComponentMask(EntityId entityId) const;

private:	
	// When entities are deleted, their EntityId index is made available again
	// Indexes tracked here to reuse them
	std::queue<EntityId> m_availableEntityIds;

	// The index in this array corresponds to an EntityId
	std::array<ComponentMask, MAX_ENTITIES> m_entities;

	// Tracks how many entities exist
	std::uint32_t m_entityCount{ 0 };
};

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