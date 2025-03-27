// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#include "CEntityManager.h"

#include <assert.h>

//------------------------------------------------------------------
CEntityManager::CEntityManager()
{
	// Cache all possible EntityIds
	for (EntityId entityId = 0; entityId < MAX_ENTITIES; ++entityId)
	{
		m_availableEntityIds.push(entityId);
	}
}

//------------------------------------------------------------------
EntityId CEntityManager::CreateEntity()
{
	// Verify that we don't have too many entities (Would overflow array)
	assert(m_entityCount < MAX_ENTITIES && !m_availableEntityIds.empty());

	EntityId entityId = m_availableEntityIds.front();
	m_availableEntityIds.pop();
	++m_entityCount;

	return entityId;
}

//------------------------------------------------------------------
void CEntityManager::DestroyEntity(EntityId entityId)
{
	// Verify entityId is valid index
	assert(entityId < MAX_ENTITIES);

	// Clear component mask of the entity
	m_entities[entityId].reset();

	// Make that index available again
	m_availableEntityIds.push(entityId);
	--m_entityCount;
}

//------------------------------------------------------------------
void CEntityManager::SetEntityComponentMask(EntityId entityId, ComponentMask componentMask)
{
	// Verify entityId is valid index
	assert(entityId < MAX_ENTITIES);

	// Update the Entity's component mask in the array
	m_entities[entityId] = componentMask;
}

//------------------------------------------------------------------
ComponentMask CEntityManager::GetEntityComponentMask(EntityId entityId) const
{
	// Verify entityId is valid index
	assert(entityId < MAX_ENTITIES);

	// Get the Entity's component mask from the array
	return m_entities[entityId];
}