// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <string>
#include <unordered_map>

//------------------------------------------------------------------
class CSpriteDataLoader
{
public:
	void LoadSpriteSheetFromJson(const std::string& data);

private:
	struct SSpriteSheet
	{

	};

	// Loaded SpriteSheets, mapped by SpriteSheet name
	std::unordered_map<std::string, SSpriteSheet> m_spriteSheets;
};