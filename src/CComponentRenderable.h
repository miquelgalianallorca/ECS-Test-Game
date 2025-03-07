// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "IComponent.h"

#include <array>
#include <memory> // for std::shared_ptr
#include <string>

struct IShape;

// rgba
typedef std::array<int, 4> TColor;

//------------------------------------------------------------------
class CComponentRenderable : public IComponent
{
public:
	// IComponent
	virtual void OnInit() override {}
	virtual void OnDone() override {}
	virtual void Update(const float& deltaTime) override {}
	virtual void Render(const float& deltaTime) override {}
	//~IComponent

	TColor GetColor() const;
	int GetLayer() const;
	std::shared_ptr<IShape> GetShape() const;

	void SetColor(const TColor& color);
	void SetLayer(const int layer);
	void SetShape(std::shared_ptr<IShape> pShape);

	static std::shared_ptr<IComponent> LoadComponentFromJson(const std::string& data);

private:
	TColor m_color;
	int m_layer{ 0 };

	std::shared_ptr<IShape> m_pShape;
	// TO DO - offsetX, offsetY
};
