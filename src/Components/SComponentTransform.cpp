// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "SComponentTransform.h"

#include "CGame.h"
#include "ECS/CEntityComponentSystem.h"
#include "json.hpp"

#include <assert.h>

using json = nlohmann::json;

//-------------------------------------------------------------------
void SComponentTransform::LoadComponentFromJson(const std::string& data, EntityId entityId)
{
	json componentData = json::parse(data);
	assert(componentData.contains("posX"));
	assert(componentData.contains("posY"));
	assert(componentData.contains("rot"));

	assert(componentData["posX"].is_number_float());
	assert(componentData["posY"].is_number_float());
	assert(componentData["rot"].is_number_float());

	SComponentTransform transform;
	transform.m_posX = componentData["posX"];
	transform.m_posY = componentData["posY"];
	transform.m_rot = componentData["rot"];

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	entityComponentSystem.AddComponent<SComponentTransform>(entityId, transform);
}