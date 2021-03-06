#include "Border.h"

#include "../../Resources/Resourcemanager.h"
#include "../../Renderer/Sprite.h"
#include "../../Physics/Collider.h"

#include <iostream>

Border::Border(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer)
	:IGameObject(position, size, rotation, layer),
	m_pCurrentSprite(ResourceManager::getSprite("wood"))
{
	m_tag = "border";

	Physics::BoxCollider colider(glm::vec2(0), m_size, this);

	colider.setCollisionCallback([&](Physics::BoxCollider* coll, glm::vec2 collisionSide) {});
	m_objectColliders.emplace_back(colider);
}

void Border::render() const
{
	m_pCurrentSprite->render(m_kinetic.getPosition(), m_size, m_kinetic.getCurrentAngle(), m_layer);
}

void Border::update(const double delta)
{
}