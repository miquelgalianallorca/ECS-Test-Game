// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "CEntityManager.h"

#include <assert.h>
#include <memory> // for std::shared_ptr

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
// Improvement: Use custom events, or some other option to avoid inheritance overhead
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
	//----------------------------------------------------------------
	virtual void OnEntityDestroyed(EntityId entityId) override
	{
		// If the destroyed Entity had this Component, remove it
		if (m_entityIdToIndexMap.find(entityId) != m_entityIdToIndexMap.end())
		{
			RemoveEntityData(entityId);
		}
	}
	//~IComponentArray

	//----------------------------------------------------------------
	void AddEntityData(EntityId entityId, T component)
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

	//----------------------------------------------------------------
	void RemoveEntityData(EntityId entityId)
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

	//----------------------------------------------------------------
	T& GetComponent(EntityId entityId)
	{
		// Verify the Entity has this Component
		assert(m_entityIdToIndexMap.find(entityId) != m_entityIdToIndexMap.end());
	
		size_t arrayIndex = m_entityIdToIndexMap[entityId];
		return m_componentArray[arrayIndex];
	}

private:
	// To identify positions in the packed array, we map EntityIds (index in the EntityManager array)
	// to their index in the component array
	// std::unordered_map:
	// - Better than std::map for performance (linked lists instead of binary tree)
	// - Improvement: Replace maps with arrays too to have contiguous memory (Code more complex)
	std::unordered_map<EntityId, size_t> m_entityIdToIndexMap;

	// We also map it the other way around, to get the EntityId of an index in the component array
	std::unordered_map<size_t, EntityId> m_indexToEntityIdMap;
	
	// The packed array of components of this type (max. 1 component per entity)
	std::array<T, MAX_ENTITIES> m_componentArray;

	// Track how many valid Entities have their component in the component array
	// Used to find last used entry in array
	size_t m_totalEntries{ 0 };
};

//------------------------------------------------------------------
// CEntityManager manages entities
// CComponentManager manages components, holding all ComponentArrays
//------------------------------------------------------------------

// Identifies a Component by being an index to the ComponentArray in CComponentManager
// It's a counter incremented each time RegisterComponent() is called
typedef std::uint8_t ComponentId;

//------------------------------------------------------------------
class CComponentManager
{
public:
	//----------------------------------------------------------------
	template<typename T>
	void RegisterComponent()
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

	//----------------------------------------------------------------
	// Return the ComponentId of a Component type (Used for creating ComponentMasks)
	template<typename T>
	ComponentId GetComponentId()
	{
		// Verify Component type has been registered
		const char* typeName = typeid(T).name();
		assert(m_componentIds.find(typeName) != m_componentIds.end());
	
		return m_componentIds[typeName];
	}

	//----------------------------------------------------------------
	template<typename T>
	void AddComponent(EntityId entityId, T component)
	{
		GetComponentArray<T>()->InsertData(entityId, component);
	}

	//----------------------------------------------------------------
	template<typename T>
	void RemoveComponent(EntityId entityId)
	{
		GetComponentArray<T>()->RemoveData(entityId);
	}

	//----------------------------------------------------------------
	template<typename T>
	T& GetComponent(EntityId entityId)
	{
		return GetComponentArray<T>()->GetData(entityId);
	}

	//----------------------------------------------------------------
	void OnEntityDestroyed(EntityId entityId);

private:
	// Map from type string pointer to a ComponentId
	std::unordered_map<const char*, ComponentId> m_componentIds;

	// Map from type string pointer to a ComponentArray
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays;

	// The ComponentId to be assigned to the next registered component
	ComponentId m_nextComponentId{ 0 };

	//----------------------------------------------------------------
	// Reused function to get a specific ComponentArray already casted to its type
	template<typename T>
	std::shared_ptr<CComponentArray<T>> GetComponentArray()
	{
		// Verify that the component has been registered
		const char* typeName = typeid(T).name();
		assert(m_componentIds.find(typeName) != m_componentIds.end());
	
		return std::static_pointer_cast<CComponentArray<T>>(m_componentIds[typeName]);
	}
};