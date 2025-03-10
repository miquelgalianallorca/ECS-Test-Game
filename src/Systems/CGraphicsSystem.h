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

private:
	// Test
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	int ball_x = 100;
	int ball_y = 100;
	int ball_speed_x = 5;
	int ball_speed_y = 5;
	int ball_radius = 15;
	//~Test
};