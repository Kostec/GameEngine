#include "IGameObject.h"
#include <math.h>

IGameObject::IGameObject(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	:m_size(size), m_layer(layer), m_direction(0, 1), m_kinetic(position, glm::vec2(0), glm::vec2(0), rotation), m_tag("object")
{

}

IGameObject::IGameObject(IGameObject& object)
{
	m_size = object.m_size;
	m_kinetic = object.m_kinetic;
	m_layer = object.m_layer;
	m_direction = object.m_direction;

	for (auto currentCollider : object.m_colliders)
	{
		m_colliders.emplace_back(currentCollider);
	}
}

void IGameObject::update(const double delta)
{
	m_kinetic.update(delta);
}

