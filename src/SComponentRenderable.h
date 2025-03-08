// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

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
	static std::shared_ptr<IComponent> LoadComponentFromJson(const std::string& data);

	TColor m_color;
	int m_layer{ 0 };
	std::shared_ptr<IShape> m_pShape;
	// TO DO - offsetX, offsetY
};
