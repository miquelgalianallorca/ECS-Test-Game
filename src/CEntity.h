// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include <memory> // for std::shared_ptr
#include <string> // for std::string
#include <vector> // for std::vector

struct IComponent;

//------------------------------------------------------------------
typedef unsigned int EntityId;

//------------------------------------------------------------------
class CEntity
{
public:
	CEntity(EntityId entityId, std::string&& name);

	void OnInit();
	void OnDone();
	void Update(const float& deltaTime);
	void Render(const float& deltaTime);

	EntityId GetEntityId() const;
	const std::string& GetName() const;

	void AddComponent(std::shared_ptr<IComponent> pComponent);

private:
	EntityId m_entityId{ 0 };
	std::string m_name;

	// In a pure ECS an Entity is just an ID associated to a collection of components, it has no logic
	// Entity: just an Id
	// Component: just data
	// System: logic for a group of components, only on Entities that have all the components the system needs
	std::vector<std::shared_ptr<IComponent>> m_components;
};

// TO DO: Add systems
// graphics system: needs transform and shape components
// physics system: needs transform and collider/rigidbody components
