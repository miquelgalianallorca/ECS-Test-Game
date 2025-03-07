// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentCollider.h"
#include "IShape.h"
#include "json.hpp"

#include <iostream>

using nlohmann::json;

#define LogError(str) std::cerr << str << std::endl

//------------------------------------------------------------------
float CComponentCollider::GetVelocityX() const
{
	return m_velocityX;
}

//------------------------------------------------------------------
float CComponentCollider::GetVelocityY() const
{
	return m_velocityY;
}

//------------------------------------------------------------------
std::shared_ptr<IShape> CComponentCollider::GetShape() const
{
	return m_pShape;
}

//------------------------------------------------------------------
void CComponentCollider::SetVelocity(const float& velocityX, const float& velocityY)
{
	m_velocityX = velocityX;
	m_velocityY = velocityY;
}

//------------------------------------------------------------------
void CComponentCollider::SetShape(std::shared_ptr<IShape> pShape)
{
	m_pShape = pShape;
}

//-------------------------------------------------------------------
std::shared_ptr<IComponent> CComponentCollider::LoadComponentFromJson(const std::string& data)
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

	std::shared_ptr<CComponentCollider> pCollider = std::make_shared<CComponentCollider>();
	pCollider->SetShape(pShape);
	pCollider->SetVelocity(componentData["velocityX"], componentData["velocityY"]);

	return pCollider;
}