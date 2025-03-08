// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "SComponentRenderable.h"
#include "IShape.h"
#include "json.hpp"

#include <iostream>

using nlohmann::json;

#define LogError(str) std::cerr << str << std::endl

//-------------------------------------------------------------------
std::shared_ptr<IComponent> SComponentRenderable::LoadComponentFromJson(const std::string& data)
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
		return nullptr;
	}

	std::shared_ptr<SComponentRenderable> pRenderable = std::make_shared<SComponentRenderable>();
	pRenderable->m_pShape = pShape;
	pRenderable->m_layer = componentData["layer"];
	pRenderable->m_color = TColor
	{
		componentData["r"],
		componentData["g"],
		componentData["b"],
		componentData["a"]
	};

	return pRenderable;
}