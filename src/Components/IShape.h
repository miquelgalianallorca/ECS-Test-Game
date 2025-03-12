// Author: Miquel Galiana Llorca
// Project: Larian Test

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