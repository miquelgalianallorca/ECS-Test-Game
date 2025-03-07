// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "IComponent.h"

#include <memory> // for std::shared_ptr
#include <string> // for std::string

class CComponentTransform : public IComponent
{
public:
	// IComponent
	virtual void OnInit() override;
	virtual void OnDone() override;
	virtual void Update(const float& deltaTime) override;
	virtual void Render(const float& deltaTime) override;
	//~IComponent

	void SetPos(const float& posX, const float& posY);
	void SetRot(const float& rot);
	float GetPosX() const;
	float GetPosY() const;
	float GetRot() const;

	static std::shared_ptr<IComponent> LoadComponentFromJson(const std::string& data);

private:
	float m_posX{ 0.f };
	float m_posY{ 0.f };
	float m_rot{ 0.f };
};