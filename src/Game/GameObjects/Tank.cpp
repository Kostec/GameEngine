#include "Tank.h"

#include "..\..\Renderer\Sprite.h"
#include "..\..\Resources\Resourcemanager.h"
#include <iostream>

Tank::Tank(const double maxVelocity,
	const glm::vec2 position,
	const glm::vec2 size,
	const float layer)
	: IGameObject(position, size, 0, layer),
	m_eorientation(EOrientation::Top),
	m_Sprite_top(ResourceManager::getSprite("tankSprite_top")),
	m_Sprite_bottom(ResourceManager::getSprite("tankSprite_bottom")),
	m_Sprite_left(ResourceManager::getSprite("tankSprite_left")),
	m_Sprite_right(ResourceManager::getSprite("tankSprite_right")),

	m_Sprite_respawn(ResourceManager::getSprite("respawn")),
	m_spriteAnimator_respawn(m_Sprite_respawn),
	m_Sprite_shield(ResourceManager::getSprite("shield")),
	m_spriteAnimator_shield(m_Sprite_shield),

	m_spriteAnimator_top(m_Sprite_top),
	m_spriteAnimator_bottom(m_Sprite_bottom),
	m_spriteAnimator_left(m_Sprite_left),
	m_spriteAnimator_right(m_Sprite_right),
	m_MaxVelocity(maxVelocity),
	m_isSpawning(true),
	m_isShield(false)
{
	m_respawnTimer.setCallback([&]() {
		m_isSpawning = false;
		m_isShield = true;
		m_shieldTimer.start(2000);
	});

	m_respawnTimer.start(1500);

	m_shieldTimer.setCallback([&]() {
		m_isShield = false;
	});

	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Tank::setOrientation(const EOrientation eOrientation)
{
	if (m_eorientation == eOrientation) return;

	m_eorientation = eOrientation;

	switch (m_eorientation)
	{
	case EOrientation::Top:
		m_direction.x = 0.f;
		m_direction.y = 1.f;
		break;
	case EOrientation::Bottom:
		m_direction.x = 0.f;
		m_direction.y = -1.f;
		break;
	case EOrientation::Left:
		m_direction.x = -1.f;
		m_direction.y = 0.f;
		break;
	case EOrientation::Right:
		m_direction.x = 1.f;
		m_direction.y = 0.f;
		break;
	}
}

void Tank::update(const double delta)
{
	if (m_isSpawning)
	{
		m_spriteAnimator_respawn.update(delta);
		m_respawnTimer.update(delta);
	}
	else
	{
		if (m_isShield)
		{
			m_spriteAnimator_shield.update(delta);
			m_shieldTimer.update(delta);
		}

		if (m_velocity.x != 0 || m_velocity.y != 0)
		{
			switch (m_eorientation)
			{
			case EOrientation::Top:
				m_spriteAnimator_top.update(delta);
				break;
			case EOrientation::Bottom:
				m_spriteAnimator_bottom.update(delta);
				break;
			case EOrientation::Left:
				m_spriteAnimator_left.update(delta);
				break;
			case EOrientation::Right:
				m_spriteAnimator_right.update(delta);
				break;
			}
		}
	}
}

void Tank::render() const
{
	if (m_isSpawning)
	{
		m_Sprite_respawn->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_respawn.getCurrentFrame());
	}
	else
	{
		switch (m_eorientation)
		{
		case EOrientation::Top:
			m_Sprite_top->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_top.getCurrentFrame());
			break;
		case EOrientation::Bottom:
			m_Sprite_bottom->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_bottom.getCurrentFrame());
			break;
		case EOrientation::Left:
			m_Sprite_left->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_left.getCurrentFrame());
			break;
		case EOrientation::Right:
			m_Sprite_right->render(m_position, m_size, m_rotation, m_layer, m_spriteAnimator_right.getCurrentFrame());
			break;
		}

		if (m_isShield)
		{
			m_Sprite_shield->render(m_position, m_size, m_rotation, m_layer + 0.1f, m_spriteAnimator_shield.getCurrentFrame());
		}
	}
}

void Tank::setVelocity(const glm::vec2 velocity)
{
	if (!m_isSpawning)
	{
		IGameObject::setVelocity(velocity);
		//m_velocity = velocity;
		std::cout << "tank velocity: " << m_velocity.x << " " << m_velocity.y << " " << m_absoluteVelocity << std::endl;
	}
}

void Tank::movingKeyCallback(EOrientation eOrientation, glm::vec2 velocity)
{
	setOrientation(eOrientation);
	setVelocity(velocity);
}