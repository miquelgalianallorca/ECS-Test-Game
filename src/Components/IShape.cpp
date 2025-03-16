// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "IShape.h"

#include "CGame.h"
#include "Components/CSpriteDataLoader.h"
#include "json.hpp"

#include <iostream>
#include <raylib.h>

using nlohmann::json;

#define LogDebug(str, type) std::cout << str << " - Type: " << type << std::endl
#define LogError(str, type) std::cerr << str << " - Type: " << type << std::endl

//------------------------------------------------------------------
S2DModel::EAnimationType GetAnimationType(const std::string& animationTypeStr)
{
	if (animationTypeStr == "idle")
		return S2DModel::EAnimationType::Idle;
	if (animationTypeStr == "move")
		return S2DModel::EAnimationType::Move;
	if (animationTypeStr == "attack")
		return S2DModel::EAnimationType::Attack;
	if (animationTypeStr == "hit")
		return S2DModel::EAnimationType::Hit;
	if (animationTypeStr == "die")
		return S2DModel::EAnimationType::Die;

	// Verify unsupported AnimationType
	assert(false);
	return S2DModel::EAnimationType::Idle;
}

//------------------------------------------------------------------
std::shared_ptr<IShape> IShape::LoadFromJson(const std::string& data)
{
	json shapeData = json::parse(data);
	assert(shapeData.contains("type"));
	assert(shapeData["type"].is_string());

	const std::string& type = shapeData["type"];
	if (type == "rectangle")
	{
		assert(shapeData.contains("sizeX"));
		assert(shapeData.contains("sizeY"));
		assert(shapeData["sizeX"].is_number_float());
		assert(shapeData["sizeY"].is_number_float());

		std::shared_ptr<SRectangle> pRectangle = std::make_shared<SRectangle>();
		pRectangle->m_sizeX = shapeData["sizeX"];
		pRectangle->m_sizeY = shapeData["sizeY"];
		return pRectangle;
	}
	else if (type == "circle")
	{
		assert(shapeData.contains("radius"));
		assert(shapeData["radius"].is_number_float());
		
		std::shared_ptr<SCircle> pCircle = std::make_shared<SCircle>();
		pCircle->m_radius = shapeData["radius"];
		return pCircle;
	}
	else if (type == "2dmodel")
	{
		assert(shapeData.contains("spritesheet"));
		assert(shapeData.contains("frameLength"));
		assert(shapeData.contains("animations"));

		assert(shapeData["spritesheet"].is_string());
		assert(shapeData["frameLength"].is_number_float());
		assert(shapeData["animations"].is_array());

		std::shared_ptr<S2DModel> p2DModel = std::make_shared<S2DModel>();
		p2DModel->m_spriteSheet = shapeData["spritesheet"];
		p2DModel->m_frameLength = shapeData["frameLength"];

		for (const json& animationData : shapeData["animations"])
		{
			assert(animationData.contains("type"));
			assert(animationData.contains("name"));
			assert(shapeData["type"].is_string());
			assert(shapeData["name"].is_string());

			p2DModel->m_animations.emplace(GetAnimationType(shapeData["type"]), shapeData["name"]);
		}

		return p2DModel;
	}

	LogError("Detected invalid type", type.c_str());
	return nullptr;
}

//------------------------------------------------------------------
Color ToRaylibColor(const TColor& _color)
{
	return Color
	{
		static_cast<unsigned char>(_color[0]),
		static_cast<unsigned char>(_color[1]),
		static_cast<unsigned char>(_color[2]),
		static_cast<unsigned char>(_color[3])
	};
}

//------------------------------------------------------------------
void SRectangle::Draw(const float& posX, const float& posY, const TColor& color)
{
	DrawRectangle(posX, posY, m_sizeX, m_sizeY, ToRaylibColor(color));
}

//------------------------------------------------------------------
void SCircle::Draw(const float& posX, const float& posY, const TColor& color)
{
	DrawCircle(posX, posY, m_radius, ToRaylibColor(color));
}

//------------------------------------------------------------------
void S2DModel::Draw(const float& posX, const float& posY, const TColor& color)
{
	// Access data: Get sprite of current animation at current index
	CSpriteDataLoader& spriteDataLoader = CGame::GetInstance().GetSpriteDataLoader();
	const Texture2D& texture = spriteDataLoader.GetTexture(m_spriteSheet);
	
	const std::string& currentAnimation = m_animations[m_currentAnimation];
	Rectangle frameRectangle = spriteDataLoader.GetFrameRectangle(m_spriteSheet, currentAnimation, m_currentFrameIndex);

	// Draw sprite
	//Vector2 position{ posX, posY };
	Rectangle drawRectangle;
	//DrawTextureRec(texture, frameRectangle, position, WHITE);

	// sourceRec defines the part of the texture we use for drawing
	// destRec defines the rectangle where our texture part will fit (scaling it to fit)
	// origin defines the point of the texture used as reference for rotation and scaling
	// rotation defines the texture rotation (using origin as rotation point)
	Vector2 pivot{ 0.f, 0.f };
	DrawTexturePro(texture, frameRectangle /*sourceRec*/, drawRectangle /*destRec*/, pivot /*origin*/, 0.f /*rotation*/, WHITE);
}

#undef LogDebug
#undef LogError