#pragma once

#include "../Game/GameObjects/IGameObject.h"
#include <glm/vec2.hpp>
#include <functional>

#include "../System/Timer.h"

namespace RenderEngine {
	class Sprite;
}

namespace Physics
{
	class BoxCollider;
}

typedef std::function<void()> BlockStopped;

//typedef void (*BlockStopped)();

static const double TETRIS_BLOCK_SIZE = 8.f;

class TetrisBlock : public IGameObject
{
public:

	TetrisBlock(const glm::vec2& position, const float rotation);

	void render() const override;
	void update(const double delta) override;

	void setSprite(const std::shared_ptr<RenderEngine::Sprite> pSprite)
	{
		m_pSprite = pSprite;
	}

	void setBlockStoppedCallBack(BlockStopped blockStoppedCallback) { m_blockStoppedCallback = blockStoppedCallback; };

	virtual void keyCallback(glm::vec2 velocity);

	virtual void collisionCallback(Physics::BoxCollider* collider);

	virtual void horisontalTimerEllapsed();
protected:
	std::shared_ptr<RenderEngine::Sprite> m_pSprite;
	BlockStopped m_blockStoppedCallback;

	Timer m_horizontalTransmitTimer;

	glm::vec2 m_previousPosition;
};