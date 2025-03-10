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

private:
	// Test
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	Ball ball;
	//~Test
};