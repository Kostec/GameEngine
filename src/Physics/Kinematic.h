#pragma once

#include <math.h>
#include <glm/vec2.hpp>
#include "../Game/IUpdatable.h"
#include "../System/Events/Event.h"

class Kinetic : public IUpdatable
{
public:
	Kinetic();
	Kinetic(glm::vec2 position, glm::vec2 velocity, glm::vec2 acceleration, float angle);
	Kinetic(Kinetic& kinematic);
	Kinetic& operator = (Kinetic& kinematic);
	Kinetic(Kinetic&& kinematic) = delete;

	void setCurrentPosition(glm::vec2 newPosition);
	void setCurrentVelocity(glm::vec2 newVelocity);
	void setCurrentAcceleration(glm::vec2 newAcceleration);
	void setCurrentAngle(float newAngle);

	glm::vec2& getCurrentPosition() { return m_currentPosition; }
	glm::vec2& getCurrentVelocity() { return m_currentVelocity; }
	glm::vec2& getCurrentAcceleration() { return m_currentAcceleration; }

	glm::vec2 getPosition() const { return m_currentPosition; }
	glm::vec2 getVelocity() const { return m_currentVelocity; }
	glm::vec2 getAcceleration() const { return m_currentAcceleration; }
	float getCurrentAngle() const { return m_currentAngle; }

	float getAbsoluteVelocity() { return  sqrt(m_currentVelocity.x * m_currentVelocity.x 
											+ m_currentVelocity.x * m_currentVelocity.x); }
	float getAbsoluteAcceleration() { return sqrt(m_currentAcceleration.x * m_currentAcceleration.x 
											+ m_currentAcceleration.x * m_currentAcceleration.x); }

	void update(const double delta) override;

	Event<glm::vec2> onAccelerationChanged;
	Event<glm::vec2> onVelocityChanged;
	Event<glm::vec2> onPositionChanged;
	Event<float> onAngleChanged;

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