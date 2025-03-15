// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CPlayerControllerSystem.h"

#include "CGame.h"
#include "Components/SComponentCollider.h"
#include "Components/SComponentPlayer.h"
#include "Components/SComponentTransform.h"
#include "ECS/CEntityComponentSystem.h"

#include <cmath> // for sqrt
#include <raylib.h>

//------------------------------------------------------------------
void CPlayerControllerSystem::Init()
{
	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();

	ComponentMask playerSystemComponentMask;
	playerSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentTransform>());
	playerSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentPlayer>());
	playerSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentPlayer>());
	
	entityComponentSystem.SetSystemComponentMask<CPlayerControllerSystem>(playerSystemComponentMask);
}

//------------------------------------------------------------------
void CPlayerControllerSystem::Update(const float& deltaTime)
{	
	// Verify that we don't have more than one Player
	assert(m_viewEntityIds.size() <= 1);

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	for (const EntityId entityId : m_viewEntityIds)
	{
		SComponentTransform& transform = entityComponentSystem.GetComponent<SComponentTransform>(entityId);
		SComponentPlayer& player = entityComponentSystem.GetComponent<SComponentPlayer>(entityId);
		SComponentCollider& collider = entityComponentSystem.GetComponent<SComponentCollider>(entityId);

		// Movement input (Apply acceleration if key pressed)
		//Vector2 currentAcceleration{ collider.m_accelerationX, collider.m_accelerationY };
		Vector2 acceleration{ 0.f, 0.f };
		if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D))
			acceleration.x += 1.f;

		if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A))
			acceleration.x -= 1.f;
			
		if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
			acceleration.y -= 1.f;

		if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
			acceleration.y += 1.f;

		// Improvement: Make a GetNormalSafe of Vector2?
		float vectorLength = sqrt(acceleration.x * acceleration.x + acceleration.y * acceleration.y);
		if (vectorLength > 0.f)
		{
			// Normalize vector (Length 1) and multiply by movement acceleration to avoid diagonals being faster
			acceleration = { acceleration.x / vectorLength, acceleration.y / vectorLength };
			acceleration = { acceleration.x * player.m_movementAcceleration, acceleration.y * player.m_movementAcceleration };

			// Don't add acceleration if it would make velocity go over the Player's maxSpeed
			Vector2 nextVelocity
			{
				collider.m_velocityX + acceleration.x * deltaTime,
				collider.m_velocityY + acceleration.y * deltaTime
			};
			float nextVelocitySquared = nextVelocity.x * nextVelocity.x + nextVelocity.y * nextVelocity.y;
			if (nextVelocitySquared < (player.m_maxSpeed * player.m_maxSpeed))
			{
				collider.m_accelerationX = acceleration.x;
				collider.m_accelerationY = acceleration.y;
			}
			else
			{
				collider.m_accelerationX = 0.f;
				collider.m_accelerationY = 0.f;
			}
		}
		else
		{
			collider.m_accelerationX = 0.f;
			collider.m_accelerationY = 0.f;
		}

		// Attack input
		// ...

		// Dash input
		// ...
	}
}