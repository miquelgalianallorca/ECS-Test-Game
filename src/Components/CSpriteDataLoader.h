// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <cstdint> // for uint8_t
// Improvement: Wrappers to avoid including library here
#include <raylib.h> // for Texture2D, Rectangle
#include <string>
#include <unordered_map>

//------------------------------------------------------------------
class CSpriteDataLoader
{
public:
	void LoadSpriteSheetFromJson(const std::string& data);

	const Texture2D& GetTexture(const std::string& spriteSheetName) const;
	Rectangle GetFrameRectangle(const std::string& spriteSheetName, const std::string& animationName, uint8_t frameIndex) const;

private:
	//----------------------------------------------------------------
	struct SAnimation
	{
		// To help calculate each Sprite position in the SpriteSheet
		uint8_t m_row;
		uint8_t m_numSprites;
	};

	//----------------------------------------------------------------
	struct SSpriteSheet
	{
		// SpriteSheet image loaded in memory
		Texture2D m_texture;

		// Animation data mapped by Animation name
		std::unordered_map<std::string, SAnimation> m_animations;

		// To help calculate each Sprite position in the SpriteSheet
		uint8_t m_spriteSizeX{ 0 };
		uint8_t m_spriteSizeY{ 0 };
		uint8_t m_padding{ 0 };
	};

	// Loaded SpriteSheets, mapped by SpriteSheet name
	std::unordered_map<std::string, SSpriteSheet> m_spriteSheets;
};