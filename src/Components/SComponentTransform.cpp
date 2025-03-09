// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "SComponentTransform.h"
#include "json.hpp"

#include <assert.h>

using json = nlohmann::json;

//-------------------------------------------------------------------
std::shared_ptr<IComponent> SComponentTransform::LoadComponentFromJson(const std::string& data)
{
	json componentData = json::parse(data);
	assert(componentData.contains("posX"));
	assert(componentData.contains("posY"));
	assert(componentData.contains("rot"));

	assert(componentData["posX"].is_number_float());
	assert(componentData["posY"].is_number_float());
	assert(componentData["rot"].is_number_float());

	std::shared_ptr<SComponentTransform> pTransform = std::make_shared<SComponentTransform>();
	pTransform->m_posX = componentData["posX"];
	pTransform->m_posY = componentData["posY"];
	pTransform->m_rot = componentData["rot"];

	return pTransform;
}