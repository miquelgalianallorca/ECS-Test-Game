// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CAnimationControllerSystem.h"

#include "CGame.h"
#include "Components/IShape.h" // for S2DModel
#include "Components/SComponentCollider.h"
#include "Components/SComponentRenderable.h"
#include "Components/SComponentTransform.h"
#include "ECS/CEntityComponentSystem.h"

#include <iostream>

//------------------------------------------------------------------
void CAnimationControllerSystem::Init()
{
	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	
	ComponentMask animationControllerSystemMask;
	animationControllerSystemMask.set(entityComponentSystem.GetComponentId<SComponentCollider>());
	animationControllerSystemMask.set(entityComponentSystem.GetComponentId<SComponentRenderable>());
	animationControllerSystemMask.set(entityComponentSystem.GetComponentId<SComponentTransform>());
	//SComponentHealth

	entityComponentSystem.SetSystemComponentMask<CAnimationControllerSystem>(animationControllerSystemMask);
}

//------------------------------------------------------------------
void CAnimationControllerSystem::Update(const float& deltaTime)
{
	CEntityComponentSystem& entityComponentSystem = CGame::GetInstance().GetEntityComponentSystem();
	CSpriteDataLoader& spriteDataLoader = CGame::GetInstance().GetSpriteDataLoader();

	for (const EntityId entityId : m_viewEntityIds)
	{
		SComponentCollider& collider = entityComponentSystem.GetComponent<SComponentCollider>(entityId);
		SComponentRenderable& renderable = entityComponentSystem.GetComponent<SComponentRenderable>(entityId);
		SComponentTransform& transform = entityComponentSystem.GetComponent<SComponentTransform>(entityId);

		// Only update animated entities (Entities whose renderable shape is an animated 2D Model)
		std::shared_ptr<S2DModel> p2DModel = std::dynamic_pointer_cast<S2DModel>(renderable.m_pShape);
		if (!p2DModel)
		{
			continue;
		}

		const std::string& currentAnimation = p2DModel->m_animations[p2DModel->m_currentAnimation];
		uint8_t numFrames = spriteDataLoader.GetNumSpritesInAnimation(p2DModel->m_spriteSheet, currentAnimation);

		// Change frameLength of animation according to movement speed ("run faster or slower" effect)
		// ...

		// Update frame of the current animation
		p2DModel->m_timeSinceLastFrame += deltaTime;
		if (p2DModel->m_timeSinceLastFrame > p2DModel->m_frameLength)
		{
			++p2DModel->m_currentFrameIndex;
			if (p2DModel->m_currentFrameIndex >= numFrames)
			{
				p2DModel->m_currentFrameIndex = 0;
			}

			p2DModel->m_timeSinceLastFrame = p2DModel->m_timeSinceLastFrame - p2DModel->m_frameLength;
		}

		// If moving towards the left, flip Sprite (Negative width on frame rectangle)
		if ((collider.m_velocityX < 0 && !p2DModel->m_bFlippedX) || (collider.m_velocityX > 0 && p2DModel->m_bFlippedX))
		{
			std::cout << "flip" << std::endl;
			p2DModel->m_bFlippedX = !p2DModel->m_bFlippedX;
		}

		// Animation changes
		switch (p2DModel->m_currentAnimation)
		{
			case S2DModel::EAnimationType::Idle:
				// Change animation to movement if started moving
				if (abs(collider.m_velocityX) > 0.f || abs(collider.m_velocityY) > 0.f)
				{
					p2DModel->m_currentAnimation = S2DModel::EAnimationType::Move;
					p2DModel->m_currentFrameIndex = 0;
				}
				break;
			case S2DModel::EAnimationType::Move:
				// Change animation to idle if stopped moving
				if (collider.m_velocityX == 0.f && collider.m_velocityY == 0.f)
				{
					p2DModel->m_currentAnimation = S2DModel::EAnimationType::Idle;
					p2DModel->m_currentFrameIndex = 0;
				}
				break;
			case S2DModel::EAnimationType::Attack:
			case S2DModel::EAnimationType::Hit:
			case S2DModel::EAnimationType::Die:
				break;
			default:
				// Verify unhandled Animation type for Animation changes
				assert(false);
				break;
		}
	}

	// Change animation to attacking if started to attack
	// ...

	// Change animation to hit if received a hit
	// ...

	// Change animation to dead if died
	// ...

}