#pragma once
#include "PhysicsEngine.h"
#include "../Game/GameObjects/IGameObject.h"
#include "../Game/ILevel.h"
#include <iostream>

namespace Physics {

	std::unordered_set<std::shared_ptr<IGameObject>> PhysicsEngine::m_dynamicObjects;
	std::shared_ptr<ILevel> PhysicsEngine::m_pCurrentLevel;

	void PhysicsEngine::init()
	{

	}

	void PhysicsEngine::terminate()
	{
		m_dynamicObjects.clear();
		m_pCurrentLevel.reset();
	}

	void PhysicsEngine::update(const double delta)
	{
		for (auto& currentObject : m_dynamicObjects)
		{
			glm::vec2 currentVelocity = currentObject->getCurrentVelocity();
			if (currentVelocity.x != 0.f || currentVelocity.y != 0.f)
			{

				if (currentObject->getCurrentDirection().x != 0.f)
				{
					currentObject->getCurrentPosition() = glm::vec2(currentObject->getCurrentPosition().x, static_cast<unsigned int>(currentObject->getCurrentPosition().y / 4.f + 0.5f) * 4.f);
				}
				else if (currentObject->getCurrentDirection().y != 0.f)
				{
					currentObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentObject->getCurrentPosition().x / 4.f + 0.5f) * 4.f, currentObject->getCurrentPosition().y);
				}

				const glm::vec2 deltaposition = glm::vec2(currentVelocity.x * delta, currentVelocity.y * delta);
				const auto newPosition = currentObject->getCurrentPosition() + deltaposition;
				const auto& colliders = currentObject->getColliders();

				std::vector<IGameObject*> objectsToCheck = m_pCurrentLevel->getObjects();

				bool hasCollision = false;
				
				for (const auto& currentObjectToCheck : objectsToCheck)
				{
					if (!currentObjectToCheck) continue;

					const auto& collidersToCheck = currentObjectToCheck->getColliders();
					if (!collidersToCheck.empty())
					{
						if (hasIntersection(colliders, newPosition, collidersToCheck, currentObjectToCheck->getCurrentPosition()))
						{
							hasCollision = true;
							break;
						}
					}
				}

				if (!hasCollision)
				{
					currentObject->getCurrentPosition() = newPosition;
				}
				else
				{
					if (deltaposition.x != 0.f)
					{
						currentObject->getCurrentPosition() = glm::vec2(static_cast<unsigned int>(currentObject->getCurrentPosition().x / 8.f + 0.5f) * 8.f, currentObject->getCurrentPosition().y);
					}
					else if (deltaposition.y != 0.f)
					{
						currentObject->getCurrentPosition() = glm::vec2(currentObject->getCurrentPosition().x, static_cast<unsigned int>(currentObject->getCurrentPosition().y / 8.f + 0.5f) * 8.f);
					}
				}
			}
		}
	}

	void PhysicsEngine::addDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
	{
		m_dynamicObjects.insert(std::move(pGameObject));
	}

	void PhysicsEngine::removeDynamicGameObject(std::shared_ptr<IGameObject> pGameObject)
	{
		m_dynamicObjects.erase(pGameObject);
	}

	void PhysicsEngine::setCurrentLevel(std::shared_ptr<ILevel> pLevel)
	{
		m_pCurrentLevel.swap(pLevel);
	}

	bool PhysicsEngine::hasIntersection(const std::vector<AABB>& colliders1, const glm::vec2 position1,
		const std::vector<AABB>& colliders2, const glm::vec2 position2)
	{
		for (const auto& currentCollider1 : colliders1)
		{
			const glm::vec2 currentCollider1_topRight_world = currentCollider1.topRight + position1;
			const glm::vec2 currentCollider1_bottomLeft_world = currentCollider1.bottomLeft + position1;

			for (const auto& currentCollider2 : colliders2)
			{
				const glm::vec2 currentCollider2_topRight_world = currentCollider2.topRight + position2;
				const glm::vec2 currentCollider2_bottomLeft_world = currentCollider2.bottomLeft + position2;

				if (currentCollider1_bottomLeft_world.x >= currentCollider2_topRight_world.x)
					continue;
				if (currentCollider1_topRight_world.x <= currentCollider2_bottomLeft_world.x)
					continue;

				if (currentCollider1_bottomLeft_world.y >= currentCollider2_topRight_world.y)
					continue;
				if (currentCollider1_topRight_world.y <= currentCollider2_bottomLeft_world.y)
					continue;

				return true;
			}
		}

		return false;
	}
}
