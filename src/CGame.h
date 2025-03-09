// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "CComponentDataLoader.h"
#include "ECS/CEntityManager.h"

#include <memory> // for std::shared_ptr

//------------------------------------------------------------------
// Singleton - Contains component manager and game systems
class CGame
{
public:
	// Singleton pattern: Accessing single instance
	static CGame& GetInstance();
	
	// Create game systems
	void Init();

	// Access game systems
	CComponentDataLoader& GetComponentDataLoader();
	CEntityManager& GetEntityManager();

private:
	// Singleton pattern: No copying, assigning or creating more instances
	CGame() = default;
	CGame(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame& operator=(CGame&&) = delete;

	// Handles loading components from data
	CComponentDataLoader m_componentDataLoader;

	// Entity Component System (ECS)
	CEntityManager m_entityManager;

	//CGraphicsSystem m_graphicsSystem;
	//CPhysicsSystem m_physicsSystem;

	// Handles loading maps, switching maps, async loading?
	//CMapManager m_mapManager;

	// Handles mouse & keyboard input
	//CInputManager m_inputManager;
};