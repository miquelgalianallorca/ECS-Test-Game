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
	struct STransform
	{
		float posX{ 0.f };
		float posY{ 0.f };
		float rot{ 0.f };
		// Scale?
	};

	CEntity(EntityId entityId, std::string&& name, STransform&& transform);

	void OnInit();
	void OnDone();
	void Update(const float& deltaTime);
	void Render(const float& deltaTime);

	EntityId GetEntityId() const;

private:
	EntityId m_entityId{ 0 };
	std::string m_name;

	// Improvement: Make transform a component (always mandatory)
	STransform m_transform;

	// In a pure ECS an Entity is just an ID associated to a collection of components
	// A System operates only on Entities that have all the components the system needs
	std::vector<std::shared_ptr<IComponent>> m_components;
};

// TO DO: Add systems
// graphics system: needs transform and shape components
// physics system: needs transform and collider/rigidbody components

// component manager singleton
// all components add themselves to the singleton (via macro?)
// unordered map of [componentName, &loadFromJsonFunction(json)]
// then the map can do load(componentName) and get an IComponent* from he loadFromJsonFunction when reading data from the file
