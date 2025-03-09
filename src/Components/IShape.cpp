// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "IShape.h"
#include "json.hpp"

#include <iostream>

using nlohmann::json;

#define LogDebug(str, type) std::cout << str << " - Type: " << type << std::endl
#define LogError(str, type) std::cerr << str << " - Type: " << type << std::endl

//------------------------------------------------------------------
std::shared_ptr<IShape> IShape::LoadFromJson(const std::string& data)
{
	json shapeData = json::parse(data);
	assert(shapeData.contains("type"));
	assert(shapeData["type"].is_string());

	const std::string& type = shapeData["type"];
	if (type == "rectangle")
	{
		assert(shapeData.contains("sizeX"));
		assert(shapeData.contains("sizeY"));
		assert(shapeData["sizeX"].is_number_float());
		assert(shapeData["sizeY"].is_number_float());

		std::shared_ptr<SRectangle> pRectangle = std::make_shared<SRectangle>();
		pRectangle->m_sizeX = shapeData["sizeX"];
		pRectangle->m_sizeY = shapeData["sizeY"];
		return pRectangle;
	}
	else if (type == "circle")
	{
		assert(shapeData.contains("radius"));
		assert(shapeData["radius"].is_number_float());
		
		std::shared_ptr<SCircle> pCircle = std::make_shared<SCircle>();
		pCircle->m_radius = shapeData["radius"];
		return pCircle;
	}

	LogError("Detected invalid type", type.c_str());
	return nullptr;
}

#undef LogDebug
#undef LogError