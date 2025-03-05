// Author: Miquel Galiana Llorca
// Project: Larian Test

#include <iostream>
#include <raylib.h>

#include "Map.h"

// Resources
// ------------------------------------------------------------------
// https://www.raylib.com/index.html
// https://github.com/educ8s/Raylib-CPP-Starter-Template-for-VSCODE
// ------------------------------------------------------------------

// ------------------------------------------------------------------
int main ()
{
	const float UPDATE_TIME = 0.15;

	// Set startup map
	Map currentMap;
	if (!currentMap.LoadMap("resources/arena.xml"))
	{
		// Error: couldn't load map
		return 0;
	}
	currentMap.OnInit();

	// Main loop of the application
	float lastUpdateTime = 0.f;
	float lastRenderTime = 0.f;
	while (!WindowShouldClose())
	{
		// Update all components on all entities
		const float currentTime = 0.f;
		const float updateDeltaTime = currentTime - lastUpdateTime;
		if (updateDeltaTime >= UPDATE_TIME)
		{
			currentMap.Update(updateDeltaTime);
			lastUpdateTime = currentTime;
		}

		// Render graphics, animations, etc.
		const float renderDeltaTime = currentTime - lastRenderTime;
		currentMap.Render(renderDeltaTime);
	}

	CloseWindow();
}