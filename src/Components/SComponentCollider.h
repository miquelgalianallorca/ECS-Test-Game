// Author: Miquel Galiana Llorca
// Project: Larian Test

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
	// TO DO - offsetX, offsetY
	// TO DO - mass and acceleration? Turn into rigidbody?
};