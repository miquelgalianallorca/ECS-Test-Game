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
	m_componentDataLoader.Init();
	// ...
}

//------------------------------------------------------------------
CComponentDataLoader& CGame::GetComponentDataLoader()
{
	return m_componentDataLoader;
}

//------------------------------------------------------------------
CEntitySystem& CGame::GetEntitySystem()
{
	return m_entitySystem;
}