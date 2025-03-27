// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#pragma once

#include "Components/CComponentDataLoader.h"
#include "Components/CSpriteDataLoader.h"
#include "ECS/CEntityComponentSystem.h"

#include <memory> // for std::shared_ptr

//------------------------------------------------------------------
// Game global variables
const float UPDATE_TIME = 0.15f;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
//------------------------------------------------------------------

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
	CSpriteDataLoader& GetSpriteDataLoader();
	CEntityComponentSystem& GetEntityComponentSystem();

private:
	// Singleton pattern: No copying, assigning or creating more instances
	CGame() = default;
	CGame(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame& operator=(CGame&&) = delete;

	// Handles loading components from data
	CComponentDataLoader m_componentDataLoader;

	// Handles loading spritesheet textures from data
	// RenderableComponent sprites can just reference data loaded once in the DataLoader
	CSpriteDataLoader m_spriteDataLoader;

	// Entity Component System (ECS) wrapper
	CEntityComponentSystem m_entityComponentSystem;

	// Handles loading maps, switching maps, async loading?
	//CMapManager m_mapManager;
};