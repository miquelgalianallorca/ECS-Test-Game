// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentRenderable.h"
#include "IShape.h"
#include "json.hpp"

#include <iostream>

using nlohmann::json;

#define LogError(str) std::cerr << str << std::endl

//------------------------------------------------------------------
TColor CComponentRenderable::GetColor() const
{
	return m_color;
}

//------------------------------------------------------------------
int CComponentRenderable::GetLayer() const
{
	return m_layer;
}

//------------------------------------------------------------------
std::shared_ptr<IShape> CComponentRenderable::GetShape() const
{
	return m_pShape;
}

//------------------------------------------------------------------
void CComponentRenderable::SetColor(const TColor& color)
{
	m_color = color;
}

//------------------------------------------------------------------
void CComponentRenderable::SetLayer(const int layer)
{
	m_layer = layer;
}

//------------------------------------------------------------------
void CComponentRenderable::SetShape(std::shared_ptr<IShape> pShape)
{
	m_pShape = pShape;
}

//-------------------------------------------------------------------
std::shared_ptr<IComponent> CComponentRenderable::LoadComponentFromJson(const std::string& data)
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

	std::shared_ptr<CComponentRenderable> pRenderable = std::make_shared<CComponentRenderable>();
	pRenderable->SetShape(pShape);
	pRenderable->SetLayer(componentData["layer"]);
	pRenderable->SetColor({
		componentData["r"],
		componentData["g"],
		componentData["b"],
		componentData["a"]
	});

	return pRenderable;
}