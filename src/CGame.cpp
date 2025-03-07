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
	// ...
}
