// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "SComponentCollider.h"

#include "CGame.h"
#include "ECS/CEntityComponentSystem.h"
#include "IShape.h"
#include "json.hpp"

#include <iostream>

using nlohmann::json;

#define LogError(str) std::cerr << str << std::endl

//-------------------------------------------------------------------
void SComponentCollider::LoadComponentFromJson(const std::string& data, EntityId entityId)
{
	json componentData = json::parse(data);
	assert(componentData.contains("velocityX"));
	assert(componentData.contains("velocityY"));
	assert(componentData.contains("shape"));
	//assert(componentData.contains("velocityRot"));

	assert(componentData["velocityX"].is_number_float());
	assert(componentData["velocityY"].is_number_float());
	//assert(componentData["velocityRot"].is_number_float());

	std::shared_ptr<IShape> pShape = IShape::LoadFromJson(componentData["shape"].dump());
	if (!pShape)
	{
		LogError("Invalid Shape data in Collider component");
		return;
	}

	SComponentCollider collider;
	collider.m_pShape = pShape;
	collider.m_velocityX = componentData["velocityX"];
	collider.m_velocityY = componentData["velocityY"];

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	entityComponentSystem.AddComponent<SComponentCollider>(entityId, collider);
}