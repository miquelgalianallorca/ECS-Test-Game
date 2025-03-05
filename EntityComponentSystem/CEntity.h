// Author: Miquel Galiana Llorca
// Project: Larian Test

#pragma once

//------------------------------------------------------------------
typedef unsigned int EntityId;

//------------------------------------------------------------------
class CEntity
{
public:
	void OnInit();
	void OnDone();
	void Update(const float& deltaTime);
	void Render(const float& deltaTime);

	EntityId GetEntityId() const;

private:
	EntityId m_entityId{ 0 };
};