// Author: Miquel Galiana Llorca
// Project: ECS Test Game

#include "CComponentManager.h"

//------------------------------------------------------------------
void CComponentManager::OnEntityDestroyed(EntityId entityId)
{
	// Notify each component array that an entity has been destroyed
	// If it has a component for that entity, it will remove it
	for (const auto& pair : m_componentArrays)
	{
		const std::shared_ptr<IComponentArray> pComponentArray = pair.second;
		pComponentArray->OnEntityDestroyed(entityId);
	}
}