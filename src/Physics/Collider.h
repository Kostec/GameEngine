#pragma once

#include <glm/vec2.hpp>

#include <functional>
#include <vector>
#include <memory>

#include "../System/Events/Event.h"

class IGameObject;

namespace Physics {
	class BoxCollider
	{
	public:
		typedef std::function<void(BoxCollider, glm::vec2)> CollisionCallbackFunc;

		Event<Physics::BoxCollider*, glm::vec2> onCollision;

		glm::vec2 bottomLeft;
		glm::vec2 topRight;

		BoxCollider(const glm::vec2 _bottomLeft, const glm::vec2 _topRight, IGameObject* parent);
		
		void setCollisionCallback(std::function<void(Physics::BoxCollider*, glm::vec2)> func) { m_collisionCallback = func; }

		void checkCollision(std::vector<IGameObject*> gameObjects);

		void setParent(IGameObject* gameObject) { m_parent = gameObject; }

		IGameObject* getParent() { return m_parent; }

	private:
		std::function<void(Physics::BoxCollider*, glm::vec2)> m_collisionCallback;

		IGameObject* m_parent;
	};
};