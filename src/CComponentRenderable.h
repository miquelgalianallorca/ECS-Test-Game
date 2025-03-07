// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

#include "IComponent.h"

#include <memory> // for std::shared_ptr
#include <string> // for std::string

class CComponentRenderable : public IComponent
{
public:
	// IComponent
	virtual void OnInit() override {}
	virtual void OnDone() override {}
	virtual void Update(const float& deltaTime) override {}
	virtual void Render(const float& deltaTime) override {}
	//~IComponent

private:

};
