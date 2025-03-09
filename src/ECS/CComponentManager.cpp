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

//------------------------------------------------------------------
template<typename T>
void CComponentManager::RegisterComponent()
{
	// Verify we're not registering the same Component type multiple times
	const char* typeName = typeid(T).name();
	assert(m_componentIds.find(typeName) == m_componentIds.end());

	// Add this component type to the ComponentId map
	m_componentIds.insert({ typeName, m_nextComponentId });
	++m_nextComponentId;

	// Create a ComponentArray pointer and add it to the component arrays map
	m_componentArrays.insert({ typeName, std::make_shared<CComponentArray<T>>() });
}

//------------------------------------------------------------------
template<typename T>
ComponentId CComponentManager::GetComponentId()
{
	// Verify Component type has been registered
	const char* typeName = typeid(T).name();
	assert(m_componentIds.find(typeName) != m_componentIds.end());

	return m_componentIds[typeName];
}

//------------------------------------------------------------------
template<typename T>
void CComponentManager::AddComponent(EntityId entityId, T component)
{
	GetComponentArray<T>()->InsertData(entityId, component);
}

//------------------------------------------------------------------
template<typename T>
void CComponentManager::RemoveComponent(EntityId entityId)
{
	GetComponentArray<T>()->RemoveData(entityId);
}

//------------------------------------------------------------------
template<typename T>
T& CComponentManager::GetComponent(EntityId entityId)
{
	return GetComponentArray<T>()->GetData(entityId);
}

//------------------------------------------------------------------
void CComponentManager::OnEntityDestroyed(EntityId entityId)
{
	// Notify each component array that an entity has been destroyed
	// If it has a component for that entity, it will remove it
	for (const auto& pair : m_componentArrays)
	{
		const std::shared_ptr<IComponentArray> pComponentArray = pair.second;
		pComponentArray->OnEntityDestroyed(entityId);
	}
}

//------------------------------------------------------------------
template<typename T>
std::shared_ptr<CComponentArray<T>> CComponentManager::GetComponentArray()
{
	// Verify that the component has been registered
	const char* typeName = typeid(T).name();
	assert(m_componentIds.find(typeName) != m_componentIds.end());

	return std::static_pointer_cast<CComponentArray<T>>(m_componentIds[typeName]);
}