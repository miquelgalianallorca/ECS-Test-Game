// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CPhysicsSystem.h"

#include "CGame.h"
#include "Components/IShape.h"
#include "Components/SComponentCollider.h"
#include "Components/SComponentTransform.h"
#include "ECS/CEntityComponentSystem.h"

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

		// TO DO: Update velocity through acceleration
		// ...

		// Update position through velocity
		transform.m_posX += (collider.m_velocityX * deltaTime);
		transform.m_posY += (collider.m_velocityY * deltaTime);

		//if (transform.m_posX > 1000 || transform.m_posX < 0)
		//{
		//	collider.m_velocityX *= -1;
		//}

		// TO DO: Collision detection
		// ...
	}
}