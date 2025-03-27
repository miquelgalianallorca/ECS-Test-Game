// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#pragma once

#include "ECS/CSystemManager.h"

//------------------------------------------------------------------
class CPlayerControllerSystem : public CSystem
{
public:
	void Init();
	void Update(const float& deltaTime);
};