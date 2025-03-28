// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#include "CMap.h"
#include "CGame.h"
#include "ECS/CEntityComponentSystem.h"
#include "Systems/CAnimationControllerSystem.h"
#include "Systems/CGraphicsSystem.h"
#include "Systems/CPhysicsSystem.h"
#include "Systems/CPlayerControllerSystem.h"

#include <assert.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <raylib.h>

// Resources & References
// ------------------------------------------------------------------
// Raylib (Graphics library)
// https://www.raylib.com/index.html
// https://github.com/educ8s/Raylib-CPP-Starter-Template-for-VSCODE-V2
//
// JSON parser
// https://github.com/nlohmann/json
//
// ECS
// https://austinmorlan.com/posts/entity_component_system/
// https://www.david-colson.com/2020/02/09/making-a-simple-ecs.html
// https://tsprojectsblog.wordpress.com/portfolio/entity-component-system/
//
// Installing MinGW
// https://code.visualstudio.com/docs/cpp/config-mingw
//
// Music
// https://pixwlk.itch.io/petaporon
// https://opengameart.org/content/512-sound-effects-8-bit-style
//
// Images
// https://www.aseprite.org/
// https://elthen.itch.io/
// ------------------------------------------------------------------

// Improvement: Logging interface
#define LogDebug(str) std::cout << str << std::endl
#define LogError(str) std::cerr << str << std::endl

typedef std::chrono::high_resolution_clock::time_point Time;

//------------------------------------------------------------------
int main()
{
	// Init game singleton
	LogDebug("Starting game");
	CGame& game = CGame::GetInstance();
	game.Init();
	
	// Register all game Systems
	CEntityComponentSystem& entityComponentSystem = game.GetEntityComponentSystem();
	
	std::shared_ptr<CGraphicsSystem> pGraphicsSystem = entityComponentSystem.RegisterSystem<CGraphicsSystem>();
	assert(pGraphicsSystem);
	pGraphicsSystem->Init();

	std::shared_ptr<CPhysicsSystem> pPhysicsSystem = entityComponentSystem.RegisterSystem<CPhysicsSystem>();
	assert(pPhysicsSystem);
	pPhysicsSystem->Init();

	std::shared_ptr<CPlayerControllerSystem> pPlayerControllerSystem = entityComponentSystem.RegisterSystem<CPlayerControllerSystem>();
	assert(pPlayerControllerSystem);
	pPlayerControllerSystem->Init();

	std::shared_ptr<CAnimationControllerSystem> pAnimationControllerSystem = entityComponentSystem.RegisterSystem<CAnimationControllerSystem>();
	assert(pAnimationControllerSystem);
	pAnimationControllerSystem->Init();

	// Set startup map
	// Improvements: Have a Map manager, handle async loading
	CMap currentMap;
	if (!currentMap.LoadMap("resources/arena.json"))
	{
		LogError("Initial map not loaded");
		return 0;
	}

	// Main loop of the application
	Time lastUpdateTime = std::chrono::high_resolution_clock::now();
	Time lastRenderTime = std::chrono::high_resolution_clock::now();
	while (!WindowShouldClose())
	{
		// Update all components on all entities
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float updateDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastUpdateTime).count();
		if (updateDeltaTime >= UPDATE_TIME)
		{
			pPlayerControllerSystem->Update(updateDeltaTime);
			pAnimationControllerSystem->Update(updateDeltaTime);
			pPhysicsSystem->Update(updateDeltaTime);

			lastUpdateTime = currentTime;
		}

		// Render graphics, animations, etc.
		const float renderDeltaTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastRenderTime).count();
		pGraphicsSystem->Update(renderDeltaTime);
		lastRenderTime = currentTime;
	}

	LogDebug("Shutting down");
	CloseWindow();
}

#undef LogDebug
#undef LogError