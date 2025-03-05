// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <vector>

#include "CEntity.h"

//------------------------------------------------------------------
class Map
{
public:
	Map() = default;

	// Load entities/components in map from xml/json data
	bool LoadMap(const char* fileName);

	// Initialize entities/components after loading the map
	void OnInit();

	// Uninitialize entities/components before deleting the map
	void OnDone();

	// Update all entities in map, process events
	void Update(const float& deltaTime);

	// Draw all entities in map
	void Render(const float& deltaTime);

private:
	std::vector<CEntity> m_entities; 

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