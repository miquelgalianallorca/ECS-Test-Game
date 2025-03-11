// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CEntityManager.h" // for EntityId

#include <memory> // for shared_ptr

//------------------------------------------------------------------
struct IShape
{
	static std::shared_ptr<IShape> LoadFromJson(const std::string& data);
};

//------------------------------------------------------------------
struct SRectangle : public IShape
{
	float m_sizeX{ 0.f };
	float m_sizeY{ 0.f };
};

//------------------------------------------------------------------
struct SCircle : public IShape
{
	float m_radius{ 0.f };
};