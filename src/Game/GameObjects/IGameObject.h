#pragma once

#include <glm/vec2.hpp>
#include "../../Physics/PhysicsEngine.h"
#include "../../Physics/Collider.h"
#include "../IUpdatable.h"
#include "../../Physics/Kinematic.h"
#include <string>

class IGameObject : public IUpdatable
{
public:
	IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	IGameObject(IGameObject& object);

	virtual void render() const = 0;
	virtual void update(const double delta);
	Kinetic& getKinematic() { return m_kinetic; }

	const glm::vec2& getSize() const { return m_size; }
	const std::vector<Physics::AABB>& getColliders() const { return m_colliders; }
	virtual std::vector<Physics::BoxCollider>& getObjectColliders() { return m_objectColliders; }

	const std::string getTag() const { return m_tag; };
	void setTag(std::string tag) { m_tag = tag; };
	

protected:
	std::string m_tag;

	glm::vec2 m_size;
	float m_layer;

	glm::vec2 m_direction;

	std::vector<Physics::AABB> m_colliders;
	std::vector<Physics::BoxCollider> m_objectColliders;

	Kinetic m_kinetic;
};