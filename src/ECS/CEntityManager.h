// Author: Miquel Galiana Llorca
// Project: ECS Test Game

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
// - Better encapsulation: Less chances to have Component changes break unrelated Systems
//------------------------------------------------------------------

// Identifies an Entity by being an index to the Entity list in CEntityManager
typedef std::uint32_t EntityId;

// Bitmask to check which Components an Entity has
// For a System to check if it has to operate on an Entity, it would just
// need a bitwise operation to compare its signature mask with the Entity's
const int MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> ComponentMask;

// Arbitrary entity limit
const EntityId MAX_ENTITIES = 1024;

//------------------------------------------------------------------
class CEntityManager
{
public:
	CEntityManager();

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