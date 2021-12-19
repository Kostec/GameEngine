#pragma once

#include "../Game/GameObjects/IGameObject.h"
#include "TetrisBlock.h"

#include <vector>
#include <map>
#include <glm/vec2.hpp>

namespace RenderEngine {
	class Sprite;
}
namespace Physics {
	class BoxCollider;
}

//class TetrisBlock;

class TetrisFigure : public TetrisBlock
{
public:
	TetrisFigure(glm::vec2 position, std::vector<glm::vec2> blockCoors);

	void render() const override;
	void update(const double delta) override;

	void setSprite(const std::shared_ptr<RenderEngine::Sprite> pSprite);
	void keyCallback(glm::vec2 velocity) override;

	void blockStoppedCallback();
	std::vector<TetrisBlock*>& getBlocks() { return m_blocks; };
	void AddState(std::vector<glm::vec2> figureState);

	void rotate();

	void onBlockCollision(Physics::BoxCollider* collider, glm::vec2 collisionSide);

private:
	std::vector<TetrisBlock*> m_blocks;
	std::vector<std::vector<glm::vec2>> m_figureStates;
	unsigned int m_state;

	void addBlock(glm::vec2 blockCoors);
};