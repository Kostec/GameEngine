#include "TetrisBlock.h"
#include "../Renderer/Sprite.h"
#include <iostream>
#include <glm/vec2.hpp>

#include <functional>
#include "../Physics/Collider.h"
#include <math.h>

#include <iostream>
#include "../System/Events/Event.h"

TetrisBlock::TetrisBlock(const glm::vec2& position, const float rotation)
	:IGameObject(position, glm::vec2(TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE), rotation, 1.f),
	m_previousPosition(glm::vec2(0))
{
	m_colliders.emplace_back(glm::vec2(0), m_size);
	
	m_objectColliders.emplace_back(glm::vec2(0), m_size, this);

	m_objectColliders[0].setCollisionCallback([&](Physics::BoxCollider* coll) {collisionCallback(coll); });

	m_horizontalTransmitTimer.onTimerElapsed += MY_METHOD_HANDLER(TetrisBlock::horisontalTimerEllapsed);
	m_horizontalTransmitTimer.start(50);

	//m_objectColliders[0].onCollision += MY_METHOD_HANDLER(TetrisBlock::collisionCallback); // TODO crash program
}

void TetrisBlock::render() const
{
	m_pSprite->render(m_position, m_size, m_rotation, m_layer);

}

void TetrisBlock::update(const double delta)
{
	m_position.y += m_velocity.y * delta;
	m_horizontalTransmitTimer.update(delta);
}

void TetrisBlock::keyCallback(glm::vec2 velocity)
{
	m_velocity = velocity;
}

void TetrisBlock::horisontalTimerEllapsed()
{
	if (m_velocity.x > 0)
	{
		m_position.x += m_size.x;
	}
	else if (m_velocity.x < 0)
	{
		m_position.x -= m_size.x;
	}
	m_horizontalTransmitTimer.start(50);
}

void TetrisBlock::collisionCallback(Physics::BoxCollider* collider)
{
	setVelocity(glm::vec2(0, 0));
	
	if (m_blockStoppedCallback)
	{
		m_position.y = (floor(m_position.y * m_size.y) + 1) / m_size.y;
		m_blockStoppedCallback();
		m_blockStoppedCallback = nullptr;
	}
}