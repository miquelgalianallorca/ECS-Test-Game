// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#include "SComponentPlayer.h"

#include "CGame.h"
#include "ECS/CEntityComponentSystem.h"
#include "json.hpp"

using nlohmann::json;

//------------------------------------------------------------------
void SComponentPlayer::LoadComponentFromJson(const std::string& data, EntityId entityId)
{
	json componentData = json::parse(data);
	assert(componentData.contains("maxSpeed"));
	assert(componentData.contains("movementAcceleration"));

	assert(componentData["maxSpeed"].is_number_float());
	assert(componentData["movementAcceleration"].is_number_float());

	SComponentPlayer player;
	player.m_maxSpeed = componentData["maxSpeed"];
	player.m_movementAcceleration = componentData["movementAcceleration"];

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	entityComponentSystem.AddComponent<SComponentPlayer>(entityId, player);
}