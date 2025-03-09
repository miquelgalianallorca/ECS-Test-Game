// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CEntityComponentSystem.h"

#include <assert.h>

//------------------------------------------------------------------
void CEntityComponentSystem::Init()
{
	m_pComponentManager = std::make_unique<CComponentManager>();
	m_pEntityManager = std::make_unique<CEntityManager>();
	m_pSystemManager = std::make_unique<CSystemManager>();
}

//------------------------------------------------------------------
EntityId CEntityComponentSystem::CreateEntity()
{
	assert(m_pEntityManager);
	return m_pEntityManager->CreateEntity();
}

//------------------------------------------------------------------
void CEntityComponentSystem::DestroyEntity(EntityId entityId)
{
	assert(m_pEntityManager && m_pComponentManager && m_pSystemManager);
	m_pEntityManager->DestroyEntity(entityId);

	// Remove Component data from the destroyed Entity
	m_pComponentManager->OnEntityDestroyed(entityId);

	// Removed the destroyed Entity from the Systems that were tracking it
	m_pSystemManager->OnEntityDestroyed(entityId);
}

//------------------------------------------------------------------
template<typename T>
void CEntityComponentSystem::RegisterComponent()
{
	assert(m_pComponentManager);
	m_pComponentManager->RegisterComponent<T>();
}

//------------------------------------------------------------------
template<typename T>
void CEntityComponentSystem::AddComponent(EntityId entityId, T component)
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

//------------------------------------------------------------------
template<typename T>
void CEntityComponentSystem::RemoveComponent(EntityId entityId)
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

//------------------------------------------------------------------
template<typename T>
T& CEntityComponentSystem::GetComponent(EntityId entityId)
{
	assert(m_pComponentManager);
	return m_pComponentManager->GetComponent<T>(entityId);
}

//------------------------------------------------------------------
template<typename T>
ComponentId CEntityComponentSystem::GetComponentId()
{
	assert(m_pComponentManager);
	return m_pComponentManager->GetComponentId<T>();
}

//------------------------------------------------------------------
template<typename T>
std::shared_ptr<T> CEntityComponentSystem::RegisterSystem()
{
	assert(m_pSystemManager);
	return m_pSystemManager->RegisterSystem<T>();
}

//------------------------------------------------------------------
template<typename T>
void CEntityComponentSystem::SetSystemComponentMask(ComponentMask systemComponentMask)
{
	assert(m_pSystemManager);
	m_pSystemManager->SetSystemComponentMask<T>(systemComponentMask);
}