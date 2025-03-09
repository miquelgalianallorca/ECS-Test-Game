// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "CEntityManager.h"
#include "CComponentManager.h"
#include "CSystemManager.h"

//------------------------------------------------------------------
// This class coordinates EntityManager, ComponentManager and SystemManager
// We will have a single EntityComponentSystem that holds them and
// handles communication between them.
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
	void RegisterComponent();

	template<typename T>
	void AddComponent(EntityId entityId, T component);

	template<typename T>
	void RemoveComponent(EntityId entityId);

	template<typename T>
	T& GetComponent(EntityId entityId);

	template<typename T>
	ComponentId GetComponentId();
	//----------------------------------------------------------------

	// System managing
	//----------------------------------------------------------------
	template<typename T>
	std::shared_ptr<T> RegisterSystem();

	template<typename T>
	void SetSystemComponentMask(ComponentMask systemComponentMask);
	//----------------------------------------------------------------

private:
	std::unique_ptr<CComponentManager> m_pComponentManager;
	std::unique_ptr<CEntityManager>    m_pEntityManager;
	std::unique_ptr<CSystemManager>    m_pSystemManager;
};