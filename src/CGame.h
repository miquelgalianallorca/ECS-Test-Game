// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

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

private:
	// Singleton pattern: No copying, assigning or creating more instances
	CGame() = default;
	CGame(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame& operator=(CGame&&) = delete;

	//CGraphicsSystem m_graphicsSystem;
	//CPhysicsSystem m_physicsSystem;
	//CMapManager m_mapManager;
	//CInputManager m_inputManager;
	//CComponentManager m_componentManager;
};