// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CSpriteDataLoader.h"

#include "json.hpp"

#include <assert.h>

using nlohmann::json;

//------------------------------------------------------------------
void CSpriteDataLoader::LoadSpriteSheetFromJson(const std::string& data)
{
	json spriteSheetData = json::parse(data);
	assert(spriteSheetData.contains("name"));
	assert(spriteSheetData.contains("path"));
	assert(spriteSheetData.contains("spriteSizeX"));
	assert(spriteSheetData.contains("spriteSizeY"));
	assert(spriteSheetData.contains("padding"));
	assert(spriteSheetData.contains("animations"));

	assert(spriteSheetData["name"].is_string());
	assert(spriteSheetData["path"].is_string());
	assert(spriteSheetData["spriteSizeX"].is_number_unsigned());
	assert(spriteSheetData["spriteSizeY"].is_number_unsigned());
	assert(spriteSheetData["padding"].is_number_unsigned());
	assert(spriteSheetData["animations"].is_array());

	const std::string& spriteSheetName = spriteSheetData["name"];
	SSpriteSheet& spriteSheet = m_spriteSheets[spriteSheetName];

	// LoadTexture must happen after window initialization (CGraphicsSystem::Init())
	const std::string& path = spriteSheetData["path"];
	spriteSheet.m_texture = LoadTexture(path.c_str());
	spriteSheet.m_spriteSizeX = spriteSheetData["spriteSizeX"];
	spriteSheet.m_spriteSizeY = spriteSheetData["spriteSizeY"];
	spriteSheet.m_padding = spriteSheetData["padding"];

	for (const json& animationData : spriteSheetData["animations"])
	{
		assert(animationData.contains("name"));
		assert(animationData.contains("row"));
		assert(animationData.contains("numSprites"));

		assert(animationData["name"].is_string());
		assert(animationData["row"].is_number_unsigned());
		assert(animationData["numSprites"].is_number_unsigned());

		const std::string& animationName = animationData["name"];
		SAnimation& animation = spriteSheet.m_animations[animationName];
		animation.m_row = animationData["row"];
		animation.m_numSprites = animationData["numSprites"];
	}
}

//------------------------------------------------------------------
const Texture2D& CSpriteDataLoader::GetTexture(const std::string& spriteSheetName) const
{
	// Verify the Spritesheet is available
	assert(m_spriteSheets.find(spriteSheetName) != m_spriteSheets.end());
	return m_spriteSheets.at(spriteSheetName).m_texture;
}

//------------------------------------------------------------------
Rectangle CSpriteDataLoader::GetFrameRectangle(const std::string& spriteSheetName, const std::string& animationName, uint8_t frameIndex) const
{
	// Verify the Spritesheet is available
	assert(m_spriteSheets.find(spriteSheetName) != m_spriteSheets.end());
	const SSpriteSheet& spriteSheet = m_spriteSheets.at(spriteSheetName);

	// Verify the Animation is available
	assert(spriteSheet.m_animations.find(animationName) != spriteSheet.m_animations.end());
	const SAnimation& animation = spriteSheet.m_animations.at(animationName);

	// Verify the frame index exists for that Animation
	assert(frameIndex < animation.m_numSprites);
	uint8_t paddingX = spriteSheet.m_padding * (frameIndex + 1);
	uint8_t paddingY = spriteSheet.m_padding * (animation.m_row + 1);
	Rectangle frameRectangle
	{
		static_cast<float>(frameIndex * spriteSheet.m_spriteSizeX) + paddingX,      /*x*/
		static_cast<float>(animation.m_row * spriteSheet.m_spriteSizeY) + paddingY, /*y*/
		static_cast<float>(spriteSheet.m_spriteSizeX),                              /*width*/
		static_cast<float>(spriteSheet.m_spriteSizeY)                               /*height*/
	};
	return frameRectangle;
}