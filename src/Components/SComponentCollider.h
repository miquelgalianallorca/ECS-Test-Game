// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#pragma once

#include "ECS/CEntityManager.h" // for EntityId
#include "IComponent.h"

#include <memory> // for std::shared_ptr
#include <string> // for std::string

struct IShape;

//------------------------------------------------------------------
struct SComponentCollider : public IComponent
{
	static void LoadComponentFromJson(const std::string& data, EntityId entityId);

	float m_velocityX{ 0.f };
	float m_velocityY{ 0.f };
	//float m_velocityRot{ 0.f };
	std::shared_ptr<IShape> m_pShape;
	bool m_bDragEnabled{ false };

	float m_accelerationX{ 0.f };
	float m_accelerationY{ 0.f };
	// TO DO - offsetX, offsetY
	// TO DO - mass and acceleration? Turn into rigidbody?
};