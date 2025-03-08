// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CMap.h"
#include "CGame.h"

#include <iostream>
#include <raylib.h>

// Resources & References
// ------------------------------------------------------------------
// Raylib (Graphics library)
// https://www.raylib.com/index.html
// https://github.com/educ8s/Raylib-CPP-Starter-Template-for-VSCODE
//
// JSON parser
// https://github.com/nlohmann/json
//
// ECS
// https://austinmorlan.com/posts/entity_component_system/
// https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html
// ------------------------------------------------------------------

// Improvement: Logging interface
#define LogDebug(str) std::cout << str << std::endl
#define LogError(str) std::cerr << str << std::endl

//------------------------------------------------------------------
int main()
{
	const float UPDATE_TIME = 0.15;

	// Init game singleton
	CGame& game = CGame::GetInstance();
	game.Init();
	
	// Set startup map
	CMap currentMap;
	if (!currentMap.LoadMap("resources/arena.json"))
	{
		LogError("Initial map not loaded");
		return 0;
	}

	LogDebug("Starting game");
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
		lastRenderTime = currentTime;
	}

	LogDebug("Shutting down");
	currentMap.OnDone();

	CloseWindow();
}

#undef LogDebug
#undef LogError