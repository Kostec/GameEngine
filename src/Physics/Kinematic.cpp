#include "Kinematic.h"

Kinematic::Kinematic()
	:m_currentPosition(0), m_previousPosition(0),
	m_currentVelocity(0), m_previousVelocity(0),
	m_currentAcceleration(0), m_previousAcceleration(0),
	m_currentAngle(0.f), m_previousAngle(0.f) 
{
}

Kinematic::Kinematic(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration, float angle)
	:m_currentPosition(position), m_previousPosition(position),
	m_currentVelocity(velocity), m_previousVelocity(velocity),
	m_currentAcceleration(acceleration), m_previousAcceleration(acceleration),
	m_currentAngle(angle), m_previousAngle(angle)
{

}

void Kinematic::setCurrentPoition(glm::vec2 newPosition)
{
	m_currentPosition = newPosition; 
	if (m_currentPosition != m_previousPosition)
	{
		onPoitionChanged(m_currentPosition);
		m_previousPosition = m_currentPosition;
	}
}

void Kinematic::setCurrentVelocity(glm::vec2 newVelocity)
{
	m_currentVelocity = newVelocity; 
	if (m_previousVelocity != m_currentVelocity)
	{
		onVelocityChanged(m_currentVelocity);
		m_previousVelocity = m_currentVelocity;
	}
}

void Kinematic::setCurrentAcceleration(glm::vec2 newAcceleration)
{
	m_currentAcceleration = newAcceleration; 
	if (m_previousAcceleration != m_currentAcceleration)
	{
		onAccelerationChanged(m_currentAcceleration);
		m_previousAcceleration = m_currentAcceleration;
	}
}

void Kinematic::setCurrentAngle(float newAngle)
{
	m_currentAngle = newAngle; 
	if (m_previousAngle == m_currentAngle)
	{
		onAngleChanged(m_currentAngle);
		m_previousAngle = m_currentAngle;
	}
}

void Kinematic::update(const double delta)
{
	m_currentVelocity += m_currentAcceleration * glm::vec2(delta);
	if (m_previousVelocity != m_currentVelocity)
	{
		onVelocityChanged(m_currentVelocity);
		m_previousVelocity = m_currentVelocity;
	}

	m_currentPosition += m_currentVelocity * glm::vec2(delta);
	if (m_currentPosition != m_previousPosition)
	{
		onPoitionChanged(m_currentPosition);
		m_previousPosition = m_currentPosition;
	}

	if (m_currentAngle != m_previousAngle)
	{
		onAngleChanged(m_currentAngle);
		m_previousAngle = m_currentAngle;
	}
}