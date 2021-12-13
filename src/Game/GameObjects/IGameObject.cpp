#include "IGameObject.h"
#include <math.h>

IGameObject::IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	:m_position(position), m_size(size), m_rotation(rotation), m_layer(layer), m_direction(0, 1), m_velocity(glm::vec2(0)), m_absoluteVelocity(0), m_tag("object")
{

}

IGameObject::IGameObject(IGameObject& object)
{
	m_position = object.m_position;
	m_size = object.m_size;
	m_rotation = object.m_rotation;
	m_layer = object.m_layer;
	m_direction = object.m_direction;
	m_velocity = object.m_velocity;
	m_absoluteVelocity = object.m_absoluteVelocity;

	for (auto currentCollider : object.m_colliders)
	{
		m_colliders.emplace_back(currentCollider);
	}
}

void IGameObject::setVelocity(const glm::vec2 velocity)
{
	m_velocity = velocity;
	calculateAbsoluteVelocity();
}
