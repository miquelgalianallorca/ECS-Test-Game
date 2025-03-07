// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CComponentTransform.h"
#include "CComponentManager.h"
#include "json.hpp"

#include <assert.h>

using json = nlohmann::json;

//CComponentManager::RegisterComponentLoadingFunction("transform", nullptr);

//-------------------------------------------------------------------
void CComponentTransform::OnInit()
{}

//-------------------------------------------------------------------
void CComponentTransform::OnDone()
{}

//-------------------------------------------------------------------
void CComponentTransform::Update(const float& deltaTime)
{}

//-------------------------------------------------------------------
void CComponentTransform::Render(const float& deltaTime)
{}

//-------------------------------------------------------------------
void CComponentTransform::SetPos(const float& posX, const float& posY)
{
	m_posX = posX;
	m_posY = posY;
}

//-------------------------------------------------------------------
void CComponentTransform::SetRot(const float& rot)
{
	m_rot = rot;
}

//-------------------------------------------------------------------
float CComponentTransform::GetPosX() const
{
	return m_posX;
}

//-------------------------------------------------------------------
float CComponentTransform::GetPosY() const
{
	return m_posY;
}

//-------------------------------------------------------------------
float CComponentTransform::GetRot() const
{
	return m_rot;
}

//-------------------------------------------------------------------
std::shared_ptr<IComponent> CComponentTransform::LoadComponentFromJson(const std::string& data)
{
	json componentData = json::parse(data);	
	assert(componentData.contains("posX"));
	assert(componentData.contains("posY"));
	assert(componentData.contains("rot"));

	assert(componentData["posX"].is_number_float());
	assert(componentData["posY"].is_number_float());
	assert(componentData["rot"].is_number_float());

	std::shared_ptr<CComponentTransform> pTransform = std::make_shared<CComponentTransform>();
	pTransform->SetPos(componentData["posX"], componentData["posY"]);
	pTransform->SetRot(componentData["rot"]);

	return pTransform;
}