// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CAnimationControllerSystem.h"

#include "CGame.h"
#include "ECS/CEntityComponentSystem.h"

//------------------------------------------------------------------
void CAnimationControllerSystem::Init()
{
	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	//miquel
	// ...
}

//------------------------------------------------------------------
void CAnimationControllerSystem::Update(const float& deltaTime)
{
	// If moving left, or right, flip drawables (Sign of Collider's velocity on X coord)
	// drawing textures -> do this by using a negative width on frameRec
	// ...

	// Change framerate of animation according to movement speed
	// ...

	// Change animation to movement if started moving
	// ...

	// Change animation to idle if stopped moving
	// ...

	// Change animation to attacking if started to attack
	// ...

	// Change animation to hit if received a hit
	// ...

	// Change animation to dead if died
	// ...

	// Update frame of the current animation
	// ...
}