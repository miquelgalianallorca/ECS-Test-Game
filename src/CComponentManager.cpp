// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentManager.h"

#include <assert.h>

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