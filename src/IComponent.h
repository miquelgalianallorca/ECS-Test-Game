// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

struct IComponent
{
	virtual void OnInit() = 0;
	virtual void OnDone() = 0;

	// Improvement: Updates registered individually by particular components
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(const float& deltaTime) = 0;
};