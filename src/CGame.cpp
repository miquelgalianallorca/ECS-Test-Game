// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CGame.h"

//------------------------------------------------------------------
CGame& CGame::GetInstance()
{
	static CGame instance;
	return instance;
}

//------------------------------------------------------------------
void CGame::Init()
{
	m_entityComponentSystem.Init();

	// Will also register all components to the ECS, so the ECS's Init()
	// must happen first
	m_componentDataLoader.Init();
}

//------------------------------------------------------------------
CComponentDataLoader& CGame::GetComponentDataLoader()
{
	return m_componentDataLoader;
}

//------------------------------------------------------------------
CSpriteDataLoader& CGame::GetSpriteDataLoader()
{
	return m_spriteDataLoader;
}

//------------------------------------------------------------------
CEntityComponentSystem& CGame::GetEntityComponentSystem()
{
	return m_entityComponentSystem;
}