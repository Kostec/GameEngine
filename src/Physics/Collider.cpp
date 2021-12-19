#include "Collider.h"
#include <glm/vec2.hpp>

#include "../Game/GameObjects/IGameObject.h"

#include <iostream>

namespace Physics
{
	BoxCollider::BoxCollider(const glm::vec2 _bottomLeft, const glm::vec2 _topRight, IGameObject* parent)
		:bottomLeft(_bottomLeft), topRight(_topRight), m_parent(parent)
	{
	}

	void BoxCollider::checkCollision(std::vector<IGameObject*> gameObjects)
	{
		glm::vec2 m_worldTopRight = this->topRight + m_parent->getKinematic().getCurrentPoition();
		glm::vec2 m_worldBottomLeft = this->bottomLeft + m_parent->getKinematic().getCurrentPoition();

		for (auto& currentObject : gameObjects)
		{
			if (currentObject == m_parent) continue;

			std::vector<Physics::BoxCollider>& colliders = currentObject->getObjectColliders();

			for (auto& currentCollider : colliders)
			{
				if (&currentCollider == this) continue;

				glm::vec2 CurrentWorldTopRight = currentCollider.topRight + currentCollider.m_parent->getKinematic().getCurrentPoition();
				glm::vec2 CurrentWorldBottomLeft = currentCollider.bottomLeft + currentCollider.m_parent->getKinematic().getCurrentPoition();

				bool hasCollision = !((m_worldBottomLeft.x >= CurrentWorldTopRight.x)
					|| (m_worldTopRight.x <= CurrentWorldBottomLeft.x)
					|| (m_worldBottomLeft.y >= CurrentWorldTopRight.y)
					|| (m_worldTopRight.y <= CurrentWorldBottomLeft.y));

				if (!hasCollision) continue;

				glm::vec2 m_center = glm::vec2((m_worldTopRight.x + m_worldBottomLeft.x)/2, (m_worldTopRight.y + m_worldBottomLeft.y) / 2);
				glm::vec2 currentCenter = glm::vec2((CurrentWorldBottomLeft.x + CurrentWorldTopRight.x) / 2, (CurrentWorldBottomLeft.y + CurrentWorldTopRight.y) / 2);
				
				onCollision(&currentCollider);
				currentCollider.onCollision(this);

				if (m_collisionCallback) m_collisionCallback(&currentCollider);
				if (currentCollider.m_collisionCallback) currentCollider.m_collisionCallback(this);
			}
		}
	}
}