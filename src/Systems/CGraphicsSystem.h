// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CSystemManager.h"

//------------------------------------------------------------------
class CGraphicsSystem : public CSystem
{
public:
	void Init();
	void Update(const float& deltaTime);
};