// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "IComponent.h"

#include <memory> // for std::shared_ptr
#include <string> // for std::string

struct IShape;

//------------------------------------------------------------------
class CComponentCollider : public IComponent
{
public:
	// IComponent
	virtual void OnInit() override {}
	virtual void OnDone() override {}
	virtual void Update(const float& deltaTime) override {}
	virtual void Render(const float& deltaTime) override {}
	//~IComponent

	float GetVelocityX() const;
	float GetVelocityY() const;
	std::shared_ptr<IShape> GetShape() const;

	void SetVelocity(const float& velocityX, const float& velocityY);
	void SetShape(std::shared_ptr<IShape> pShape);

	static std::shared_ptr<IComponent> LoadComponentFromJson(const std::string& data);

private:
	float m_velocityX{ 0.f };
	float m_velocityY{ 0.f };
	//float m_velocityRot{ 0.f };
	
	std::shared_ptr<IShape> m_pShape;
	// TO DO - offsetX, offsetY
	// TO DO - mass and acceleration? Turn into rigidbody?
};