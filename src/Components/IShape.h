// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#pragma once

#include "Components/SComponentRenderable.h" // for TColor
#include "ECS/CEntityManager.h"              // for EntityId

#include <memory> // for shared_ptr

//------------------------------------------------------------------
struct IShape
{
	static std::shared_ptr<IShape> LoadFromJson(const std::string& data);

	virtual void Draw(const float& posX, const float& posY, const TColor& color) = 0;

	virtual ~IShape() = default;
};

//------------------------------------------------------------------
struct SRectangle : public IShape
{
	float m_sizeX{ 0.f };
	float m_sizeY{ 0.f };

	virtual void Draw(const float& posX, const float& posY, const TColor& color) override;
};

//------------------------------------------------------------------
struct SCircle : public IShape
{
	float m_radius{ 0.f };

	virtual void Draw(const float& posX, const float& posY, const TColor& color) override;
};

//------------------------------------------------------------------
struct S2DModel : public IShape
{
	enum class EAnimationType : uint8_t
	{
		Idle,
		Move,
		Attack,
		Hit,
		Die
	};

	// Name of the Spritesheet being used by the Model
	std::string m_spriteSheet;
	float m_sizeX{ 0.f };
	float m_sizeY{ 0.f };
	bool m_bFlippedX{ false };

	// Framerate of the animation
	// Improvement: Change running animation speed depending on character speed?
	float m_frameLength{ 0.125f }; // 8 FPS
	float m_timeSinceLastFrame{ 0.f };

	// Animation names mapped to each EAnimationType
	std::unordered_map<EAnimationType, std::string> m_animations; 
	EAnimationType m_currentAnimation{ EAnimationType::Idle };
	uint8_t m_currentFrameIndex{ 0 };

	virtual void Draw(const float& posX, const float& posY, const TColor& color) override;
};