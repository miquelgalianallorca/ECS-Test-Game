// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "ECS/CEntityManager.h" // for EntityId
#include "IComponent.h"

#include <chrono>
#include <string>

typedef std::chrono::high_resolution_clock::time_point Time;

struct SComponentTransform : public IComponent
{
	static void LoadComponentFromJson(const std::string& data, EntityId entityId);

	float m_posX{ 0.f };
	float m_posY{ 0.f };
	float m_rot{ 0.f };

	// State on the previous frame (Used for drawing in CGraphicsSystem)
	Time m_lastUpdateTime;
	float m_lastPosX{ 0.f };
	float m_lastPosY{ 0.f };
	float m_lastRot{ 0.f };
};