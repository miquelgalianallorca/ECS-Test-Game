// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#include "SComponentRenderable.h"

#include "CGame.h"
#include "ECS/CEntityComponentSystem.h"
#include "IShape.h"
#include "json.hpp"

#include <iostream>

using nlohmann::json;

#define LogError(str) std::cerr << str << std::endl

//-------------------------------------------------------------------
void SComponentRenderable::LoadComponentFromJson(const std::string& data, EntityId entityId)
{
	json componentData = json::parse(data);
	assert(componentData.contains("r"));
	assert(componentData.contains("g"));
	assert(componentData.contains("b"));
	assert(componentData.contains("a"));
	assert(componentData.contains("layer"));
	assert(componentData.contains("shape"));

	assert(componentData["r"].is_number_integer());
	assert(componentData["g"].is_number_integer());
	assert(componentData["b"].is_number_integer());
	assert(componentData["a"].is_number_integer());
	assert(componentData["layer"].is_number_integer());

	std::shared_ptr<IShape> pShape = IShape::LoadFromJson(componentData["shape"].dump());
	if (!pShape)
	{
		LogError("Invalid Shape data in Renderable component");
		return;
	}

	SComponentRenderable renderable;
	renderable.m_pShape = pShape;
	renderable.m_layer = componentData["layer"];
	renderable.m_color = TColor
	{
		componentData["r"],
		componentData["g"],
		componentData["b"],
		componentData["a"]
	};

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	entityComponentSystem.AddComponent<SComponentRenderable>(entityId, renderable);
}