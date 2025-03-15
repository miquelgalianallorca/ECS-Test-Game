// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CEntityManager.h" // for EntityId
#include "IComponent.h"

#include <string>

//------------------------------------------------------------------
struct SComponentPlayer : public IComponent
{
	static void LoadComponentFromJson(const std::string& data, EntityId entityId);

	float m_maxSpeed{ 0.f };
	float m_movementAcceleration{ 0.f };
};