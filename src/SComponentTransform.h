// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "IComponent.h"

#include <memory> // for std::shared_ptr
#include <string> // for std::string

struct SComponentTransform : public IComponent
{
	static std::shared_ptr<IComponent> LoadComponentFromJson(const std::string& data);

	float m_posX{ 0.f };
	float m_posY{ 0.f };
	float m_rot{ 0.f };
};