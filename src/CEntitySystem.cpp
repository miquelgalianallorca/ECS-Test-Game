// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CEntitySystem.h"

#include <assert.h>

//------------------------------------------------------------------
CEntitySystem::CEntitySystem()
{
	// Cache all possible EntityIds
	for (EntityId entityId = 0; entityId < MAX_ENTITIES; ++entityId)
	{
		m_availableEntityIds.push(entityId);
	}
}

//------------------------------------------------------------------
EntityId CEntitySystem::CreateEntity()
{
	// Verify that we don't have too many entities (Would overflow array)
	assert(m_entityCount < MAX_ENTITIES && !m_availableEntityIds.empty());

	EntityId entityId = m_availableEntityIds.front();
	m_availableEntityIds.pop();
	++m_entityCount;

	return entityId;
}

//------------------------------------------------------------------
void CEntitySystem::DestroyEntity(EntityId entityId)
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
void CEntitySystem::SetEntityComponentMask(EntityId entityId, ComponentMask componentMask)
{
	// Verify entityId is valid index
	assert(entityId < MAX_ENTITIES);

	// Update the Entity's component mask in the array
	m_entities[entityId] = componentMask;
}

//------------------------------------------------------------------
ComponentMask CEntitySystem::GetEntityComponentMask(EntityId entityId) const
{
	// Verify entityId is valid index
	assert(entityId < MAX_ENTITIES);

	// Get the Entity's component mask from the array
	return m_entities[entityId];
}

//------------------------------------------------------------------
template<typename T>
void CComponentArray<T>::AddEntityData(EntityId entityId, T component)
{
	// Verify we're not adding duplicate components to the same Entity
	assert(m_entityIdToIndexMap.find(entityId) == m_entityIdToIndexMap.end());

	// Add the component data at the end of the array
	size_t newIndex = m_totalEntries;
	m_componentArray[newIndex] = component;

	// Update mappings to access data with entityId and viceversa
	m_entityIdToIndexMap[entityId] = newIndex;
	m_indexToEntityIdMap[newIndex] = entityId;
	
	++m_totalEntries;
}

//------------------------------------------------------------------
template<typename T>
void CComponentArray<T>::RemoveEntityData(EntityId entityId)
{
	// Verify the Entity had this component
	assert(m_entityIdToIndexMap.find(entityId) != m_entityIdToIndexMap.end());

	// Copy the last used element into the spot of the removed one
	// to maintain packed density
	size_t removedEntityIndex = m_entityIdToIndexMap[entityId];
	size_t lastUsedIndex = m_totalEntries - 1;
	m_componentArray[removedEntityIndex] = m_componentArray[lastUsedIndex];

	// Update mappings to access the moved element
	EntityId lastUsedEntityId = m_indexToEntityIdMap[lastUsedIndex];
	m_entityIdToIndexMap[lastUsedEntityId] = removedEntityIndex;
	m_indexToEntityIdMap[removedEntityIndex] = lastUsedEntityId;

	// Remove the entityId from the mappings to access data
	m_entityIdToIndexMap.erase(entityId);
	m_indexToEntityIdMap.erase(lastUsedIndex);

	--m_totalEntries;
}

//------------------------------------------------------------------
template<typename T>
T& CComponentArray<T>::GetComponent(EntityId entityId)
{
	// Verify the Entity has this Component
	assert(m_entityIdToIndexMap.find(entityId) != m_entityIdToIndexMap.end());

	size_t arrayIndex = m_entityIdToIndexMap[entityId];
	return m_componentArray[arrayIndex];
}

//------------------------------------------------------------------
template<typename T>
void CComponentArray<T>::OnEntityDestroyed(EntityId entityId)
{
	// If the destroyed Entity had this Component, remove it
	if (m_entityIdToIndexMap.find(entityId) != m_entityIdToIndexMap.end())
	{
		RemoveEntityData(entityId);
	}
}