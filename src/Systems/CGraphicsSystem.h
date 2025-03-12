// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CSystemManager.h"

#include "ball.h" // just testing

//------------------------------------------------------------------
class CGraphicsSystem : public CSystem
{
public:
	void Init();
	void Update(const float& deltaTime);
};