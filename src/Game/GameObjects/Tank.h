#pragma once

#include <memory>

#include <glm/vec2.hpp>

#include "IGameObject.h"
#include "../../Renderer/SpriteAnimator.h"
#include "../../System/Timer.h"

namespace RenderEngine {
	class Sprite;
}

class Tank : public IGameObject
{
public:
	enum EOrientation {
		Top, Bottom, Left, Right
	};

	Tank(const double maxVelocity,
		const glm::vec2 position,
		const glm::vec2 size,
		const float layer);

	void setOrientation(const EOrientation eOrientation);

	void update(const double delta) override;
	void render() const override;

	double getMaxVelocity() const { return m_MaxVelocity; }

	//void setVelocity(const double velocity) override;
	void setVelocity(const glm::vec2 velocity) override;

	void movingKeyCallback(EOrientation eOrientation, glm::vec2 velocity);

private:
	EOrientation m_eorientation;
	std::shared_ptr<RenderEngine::Sprite> m_Sprite_top;
	std::shared_ptr<RenderEngine::Sprite> m_Sprite_bottom;
	std::shared_ptr<RenderEngine::Sprite> m_Sprite_left;
	std::shared_ptr<RenderEngine::Sprite> m_Sprite_right;

	RenderEngine::SpriteAnimator m_spriteAnimator_top;
	RenderEngine::SpriteAnimator m_spriteAnimator_bottom;
	RenderEngine::SpriteAnimator m_spriteAnimator_left;
	RenderEngine::SpriteAnimator m_spriteAnimator_right;

	std::shared_ptr<RenderEngine::Sprite> m_Sprite_respawn;
	RenderEngine::SpriteAnimator m_spriteAnimator_respawn;

	std::shared_ptr<RenderEngine::Sprite> m_Sprite_shield;
	RenderEngine::SpriteAnimator m_spriteAnimator_shield;

	Timer m_respawnTimer;
	Timer m_shieldTimer;

	double m_MaxVelocity;
	bool m_isSpawning;
	bool m_isShield;
};