#pragma once

#include <math.h>
#include <glm/vec2.hpp>
#include "../Game/IUpdatable.h"
#include "../System/Events/Event.h"

class Kinematic : public IUpdatable
{
public:
	Event<glm::vec2> onAccelerationChanged;
	Event<glm::vec2> onVelocityChanged;
	Event<glm::vec2> onPoitionChanged;
	Event<float> onAngleChanged;
public:
	Kinematic();
	Kinematic(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration, float angle);
	Kinematic(const Kinematic& kinematic) = delete;
	Kinematic(Kinematic&& kinematic) = delete;
	Kinematic& operator = (Kinematic&& kinematic) = delete;

	void setCurrentPoition(glm::vec2 newPosition);
	void setCurrentVelocity(glm::vec2 newVelocity);
	void setCurrentAcceleration(glm::vec2 newAcceleration);
	void setCurrentAngle(float newAngle);

	const glm::vec2 getCurrentPoition() const { return m_currentPosition; }
	const glm::vec2 getCurrentVelocity() const { return m_currentVelocity; }
	const glm::vec2 getCurrentAcceleration() const { return m_currentAcceleration; }
	const float getCurrentAngle() const { return m_currentAngle; }

	float getAbsoluteVelocity() { return  sqrt(m_currentVelocity.x * m_currentVelocity.x 
											+ m_currentVelocity.x * m_currentVelocity.x); }
	float getAbsoluteAcceleration() { return sqrt(m_currentAcceleration.x * m_currentAcceleration.x 
											+ m_currentAcceleration.x * m_currentAcceleration.x); }

	void update(const double delta) override;

private:
	glm::vec2 m_previousPosition;
	glm::vec2 m_previousVelocity;
	glm::vec2 m_previousAcceleration;

	float m_previousAngle;

	glm::vec2 m_currentPosition;
	glm::vec2 m_currentVelocity;
	glm::vec2 m_currentAcceleration;

	float m_currentAngle;

};