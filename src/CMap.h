// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <vector>

//------------------------------------------------------------------
class CMap
{
public:
	// Load entities/components in map from xml/json data
	bool LoadMap(const char* fileName);
};