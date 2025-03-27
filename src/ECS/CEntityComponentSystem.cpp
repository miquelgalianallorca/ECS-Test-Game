// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#include "CEntityComponentSystem.h"

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