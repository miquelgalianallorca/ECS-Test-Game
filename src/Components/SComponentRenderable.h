// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CEntityManager.h" // for EntityId
#include "IComponent.h"

#include <array>
#include <memory> // for std::shared_ptr
#include <string>

struct IShape;

// rgba
typedef std::array<int, 4> TColor;

//------------------------------------------------------------------
struct SComponentRenderable : public IComponent
{
	static void LoadComponentFromJson(const std::string& data, EntityId entityId);

	TColor m_color;
	int m_layer{ 0 };
	std::shared_ptr<IShape> m_pShape;
	// TO DO - offsetX, offsetY

	// For drawing interpolation
	float m_lastDrawPosX{ 0.f };
	float m_lastDrawPosY{ 0.f };
};
