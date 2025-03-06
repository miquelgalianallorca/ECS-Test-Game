// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CEntity.h"
#include "IComponent.h"

#include <iostream>

#define LogEntityDebug(str) std::cout << str << " - " << m_name.c_str() << "[" << m_entityId << "]" << std::endl
#define LogEntityError(str) std::cerr << str << " - " << m_name.c_str() << "[" << m_entityId << "]" << std::endl

//------------------------------------------------------------------
CEntity::CEntity(EntityId entityId, std::string&& name, STransform&& transform)
	: m_entityId(entityId)
	, m_name(name)
	, m_transform(transform)
{}

//------------------------------------------------------------------
void CEntity::OnInit()
{
	for (std::shared_ptr<IComponent> pComponent : m_components)
	{
		if (!pComponent)
		{
			LogEntityError("CEntity::OnInit - Invalid component");
			continue;
		}
		pComponent->OnInit();
	}
}

//------------------------------------------------------------------
void CEntity::OnDone()
{
	for (std::shared_ptr<IComponent> pComponent : m_components)
	{
		if (!pComponent)
		{
			LogEntityError("CEntity::OnDone - Invalid component");
			continue;
		}
		pComponent->OnDone();
	}
}

//------------------------------------------------------------------
EntityId CEntity::GetEntityId() const
{
	return m_entityId;
}

//------------------------------------------------------------------
void CEntity::Update(const float& deltaTime)
{
	// Handle events queued to entity
	// ...

	// Update components
	for (std::shared_ptr<IComponent> pComponent : m_components)
	{
		if (!pComponent)
		{
			LogEntityError("CEntity::Update - Invalid component");
			continue;
		}
		pComponent->Update(deltaTime);
	}
}

//------------------------------------------------------------------
void CEntity::Render(const float& deltaTime)
{
	for (std::shared_ptr<IComponent> pComponent : m_components)
	{
		if (!pComponent)
		{
			LogEntityError("CEntity::Render - Invalid component");
			continue;
		}
		pComponent->Render(deltaTime);
	}
}

#undef LogEntityDebug
#undef LogEntityError
