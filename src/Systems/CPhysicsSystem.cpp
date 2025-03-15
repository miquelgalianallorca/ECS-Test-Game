// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CPhysicsSystem.h"

#include "CGame.h"
#include "Components/IShape.h"
#include "Components/SComponentCollider.h"
#include "Components/SComponentTransform.h"
#include "ECS/CEntityComponentSystem.h"

#include <cmath> // for sqrt

const float EPSILON = 0.0005f;
const float DRAG = 250.f;

//------------------------------------------------------------------
void CPhysicsSystem::Init()
{
	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();

	ComponentMask physicsSystemComponentMask;
	physicsSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentTransform>());
	physicsSystemComponentMask.set(entityComponentSystem.GetComponentId<SComponentCollider>());
	
	entityComponentSystem.SetSystemComponentMask<CPhysicsSystem>(physicsSystemComponentMask);
}

//------------------------------------------------------------------
bool IsNearZero(const float& value)
{
	return value < EPSILON && value > -1 * EPSILON;
}

//------------------------------------------------------------------
void CPhysicsSystem::Update(const float& deltaTime)
{
	Time currentTime = std::chrono::high_resolution_clock::now();

	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	for (const EntityId entityId : m_viewEntityIds)
	{
		SComponentTransform& transform = entityComponentSystem.GetComponent<SComponentTransform>(entityId);
		SComponentCollider& collider = entityComponentSystem.GetComponent<SComponentCollider>(entityId);

		// Track state before Update for interpolation (ie. CGraphicsSystem)
		transform.m_lastUpdateTime = currentTime;
		transform.m_lastPosX = transform.m_posX;
		transform.m_lastPosY = transform.m_posY;
		transform.m_lastRot = transform.m_rot;

		// Update velocity through acceleration
		collider.m_velocityX += (collider.m_accelerationX * deltaTime);
		collider.m_velocityY += (collider.m_accelerationY * deltaTime);
		// angular acceleration?

		// Drag: Force opposite velocity (Simplified)
		float velocityLength = sqrt(collider.m_velocityX * collider.m_velocityX + collider.m_velocityY * collider.m_velocityY);
		if (velocityLength > 0.f)
		{
			// Normalize movement vector, invert and multiply by drag coefficient
			// Don't add drag if there's an acceleration affecting the entity
			float dragX = IsNearZero(collider.m_accelerationX) 
				? (collider.m_velocityX / velocityLength) * -1 * DRAG * deltaTime
				: 0.f;
			float dragY = IsNearZero(collider.m_accelerationY)
				? (collider.m_velocityY / velocityLength) * -1 * DRAG * deltaTime
				: 0.f;

			// Avoid drag flipping movement into the opposite direction (Causes jitter)
			if (abs(dragX) > abs(collider.m_velocityX))
			{
				collider.m_velocityX = 0.f;
			}
			else
			{
				collider.m_velocityX += dragX;
			}
			if (abs(dragY) > abs(collider.m_velocityY))
			{
				collider.m_velocityY = 0.f;
			}
			else
			{
				collider.m_velocityY += dragY;
			}
		}

		// Update position through velocity
		transform.m_posX += (collider.m_velocityX * deltaTime);
		transform.m_posY += (collider.m_velocityY * deltaTime);
		// angular velocity?

		// TO DO: Collision detection
		// ...
	}
}