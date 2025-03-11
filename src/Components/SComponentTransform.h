// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CEntityManager.h" // for EntityId
#include "IComponent.h"

#include <string> // for std::string

struct SComponentTransform : public IComponent
{
	static void LoadComponentFromJson(const std::string& data, EntityId entityId);

	float m_posX{ 0.f };
	float m_posY{ 0.f };
	float m_rot{ 0.f };
};