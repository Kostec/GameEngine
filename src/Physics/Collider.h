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
		typedef std::function<void(BoxCollider)> CollisionCallbackFunc;

		Event<Physics::BoxCollider*> onCollision;

		glm::vec2 bottomLeft;
		glm::vec2 topRight;

		BoxCollider(const glm::vec2 _bottomLeft, const glm::vec2 _topRight, IGameObject* parent);
		
		void setCollisionCallback(std::function<void(Physics::BoxCollider*)> func) { m_collisionCallback = func; }

		void checkCollision(std::vector<IGameObject*> gameObjects);

		void setParent(IGameObject* gameObject) { m_parent = gameObject; }

		IGameObject* getParent() { return m_parent; }

	private:
		std::function<void(Physics::BoxCollider*)> m_collisionCallback;

		IGameObject* m_parent;
	};
};