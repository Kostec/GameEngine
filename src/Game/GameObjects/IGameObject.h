#pragma once

#include <glm/vec2.hpp>
#include "../../Physics/PhysicsEngine.h"
#include "../../Physics/Collider.h"
#include <string>

class IGameObject
{
public:
	IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer);
	IGameObject(IGameObject& object);

	virtual void render() const = 0;
	virtual void update(const double delta) = 0;
	virtual glm::vec2& getCurrentPosition() { return m_position; }
	virtual glm::vec2& getCurrentDirection() { return m_direction; }

	virtual glm::vec2 getCurrentVelocity() { return m_velocity; }
	virtual double getAbsoluteVelocity() const { return m_absoluteVelocity; }
	virtual void setVelocity(const glm::vec2 velocity);
	virtual void addVelocity(const glm::vec2 velocity) { setVelocity(m_velocity + velocity); }

	const glm::vec2& getSize() const { return m_size; }
	const std::vector<Physics::AABB>& getColliders() const { return m_colliders; }
	virtual std::vector<Physics::BoxCollider>& getObjectColliders() { return m_objectColliders; }

	const std::string getTag() const { return m_tag; };
	void setTag(std::string tag) { m_tag = tag; };
	

protected:
	std::string m_tag;

	glm::vec2 m_position;
	glm::vec2 m_size;
	float m_rotation;
	float m_layer;

	glm::vec2 m_direction;
	glm::vec2 m_velocity;
	double m_absoluteVelocity;

	std::vector<Physics::AABB> m_colliders;
	std::vector<Physics::BoxCollider> m_objectColliders;

	virtual void calculateAbsoluteVelocity() { m_absoluteVelocity = sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y); };
};