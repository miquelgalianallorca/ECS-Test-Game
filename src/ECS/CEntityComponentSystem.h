// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#pragma once

#include "CEntityManager.h"
#include "CComponentManager.h"
#include "CSystemManager.h"

#include <assert.h>

//------------------------------------------------------------------
// This class coordinates EntityManager, ComponentManager and SystemManager
// We will have a single EntityComponentSystem that holds them and
// handles communication between them.
//
// A different way to do this is to have a CEntity class that can reach
// across these managers, for example: CEntity::RemoveComponent()
// But this way we just need a CEntityComponentSystem in our CGame
// singleton
//------------------------------------------------------------------

//------------------------------------------------------------------
class CEntityComponentSystem
{
public:
	// Create Entity, Component and System managers
	void Init();

	// Entity managing
	//----------------------------------------------------------------
	EntityId CreateEntity();
	void DestroyEntity(EntityId entityId);
	//----------------------------------------------------------------

	// Component managing
	//----------------------------------------------------------------
	template<typename T>
	void RegisterComponent()
	{
		assert(m_pComponentManager);
		m_pComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(EntityId entityId, T component)
	{
		assert(m_pEntityManager && m_pComponentManager && m_pSystemManager);
		
		// Improvement - Use std::move?
		m_pComponentManager->AddComponent<T>(entityId, component);
	
		// Update the Entity's ComponentMask
		ComponentMask componentMask = m_pEntityManager->GetEntityComponentMask(entityId);
		componentMask.set(m_pComponentManager->GetComponentId<T>(), true);
		m_pEntityManager->SetEntityComponentMask(entityId, componentMask);
	
		// Notify all Systems that the Entity's ComponentMask has changed
		// In case they need to start caring about the Entity
		m_pSystemManager->OnEntityComponentsChanged(entityId, componentMask);
	}

	template<typename T>
	void RemoveComponent(EntityId entityId)
	{
		assert(m_pEntityManager && m_pComponentManager && m_pSystemManager);
		m_pComponentManager->RemoveComponent<T>(entityId);
	
		// Update the Entity's ComponentMask
		ComponentMask componentMask = m_pEntityManager->GetEntityComponentMask(entityId);
		componentMask.set(m_pComponentManager->GetComponentId<T>(), false);
		m_pEntityManager->SetEntityComponentMask(entityId, componentMask);
	
		// Notify all Systems that the Entity's ComponentMask has changed
		// In case they need to stop caring about the Entity
		m_pSystemManager->OnEntityComponentsChanged(entityId, componentMask);
	}

	template<typename T>
	T& GetComponent(EntityId entityId)
	{
		assert(m_pComponentManager);
		return m_pComponentManager->GetComponent<T>(entityId);
	}

	template<typename T>
	ComponentId GetComponentId()
	{
		assert(m_pComponentManager);
		return m_pComponentManager->GetComponentId<T>();
	}
	//----------------------------------------------------------------

	// System managing
	//----------------------------------------------------------------
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		assert(m_pSystemManager);
		return m_pSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemComponentMask(ComponentMask systemComponentMask)
	{
		assert(m_pSystemManager);
		m_pSystemManager->SetSystemComponentMask<T>(systemComponentMask);
	}
	//----------------------------------------------------------------

private:
	std::unique_ptr<CComponentManager> m_pComponentManager;
	std::unique_ptr<CEntityManager>    m_pEntityManager;
	std::unique_ptr<CSystemManager>    m_pSystemManager;
};