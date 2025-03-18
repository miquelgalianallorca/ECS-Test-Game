// Author: Miquel Galiana Llorca
// Project: Larian Test

#include "CAnimationControllerSystem.h"

#include "CGame.h"
#include "Components/IShape.h" // for S2DModel
#include "Components/SComponentCollider.h"
#include "Components/SComponentRenderable.h"
#include "Components/SComponentTransform.h"
#include "ECS/CEntityComponentSystem.h"

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
		SComponentTransform& transform = entityComponentSystem.GetComponent<SComponentTransform>(entityId);
		SComponentRenderable& renderable = entityComponentSystem.GetComponent<SComponentRenderable>(entityId);

		// Only update animated entities (Entities whose renderable shape is an animated 2D Model)
		std::shared_ptr<S2DModel> p2DModel = std::dynamic_pointer_cast<S2DModel>(renderable.m_pShape);
		if (!p2DModel)
		{
			continue;
		}

		const std::string& currentAnimation = p2DModel->m_animations[p2DModel->m_currentAnimation];
		uint8_t numFrames = spriteDataLoader.GetNumSpritesInAnimation(p2DModel->m_spriteSheet, currentAnimation);

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

		// Animation changes
		switch (p2DModel->m_currentAnimation)
		{
			case S2DModel::EAnimationType::Idle:
				break;
		}
	}

	// If moving left, or right, flip drawables (Sign of Collider's velocity on X coord)
	// drawing textures -> do this by using a negative width on frameRec
	// downcast IShape to S2DModel
	// auto downcastedPtr = std::dynamic_pointer_cast<Derived>(basePtr);
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

}