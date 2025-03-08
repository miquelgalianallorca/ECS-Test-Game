// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "SComponentCollider.h"
#include "IShape.h"
#include "json.hpp"

#include <iostream>

using nlohmann::json;

#define LogError(str) std::cerr << str << std::endl

//-------------------------------------------------------------------
std::shared_ptr<IComponent> SComponentCollider::LoadComponentFromJson(const std::string& data)
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
		return nullptr;
	}

	std::shared_ptr<SComponentCollider> pCollider = std::make_shared<SComponentCollider>();
	pCollider->m_pShape = pShape;
	pCollider->m_velocityX = componentData["velocityX"];
	pCollider->m_velocityY = componentData["velocityY"];

	return pCollider;
}