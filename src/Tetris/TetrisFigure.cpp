#include "TetrisFigure.h"

#include "TetrisBlock.h"
#include "../Renderer/Sprite.h"

#include <iostream>
#include <math.h>

TetrisFigure::TetrisFigure(glm::vec2 position, std::vector<glm::vec2> blockCoors)
	:TetrisBlock(position, 0)
{
	m_objectColliders.clear();
	for (auto currentBlockCoor : blockCoors)
	{
		addBlock(currentBlockCoor);
	}
	m_figureStates.emplace_back(blockCoors);
	m_state = 0;
}

void TetrisFigure::addBlock(glm::vec2 blockCoors)
{
	TetrisBlock* block = new TetrisBlock(blockCoors + m_position, 0);
	block->setBlockStoppedCallBack([&]() {blockStoppedCallback(); });
	m_blocks.emplace_back(block);

	auto& blockColliders = block->getObjectColliders();
	m_objectColliders.insert(m_objectColliders.end(), blockColliders.begin(), blockColliders.end());

	for (auto& collider : blockColliders)
	{
		collider.onCollision += MY_METHOD_HANDLER(TetrisFigure::onBlockCollision);
	}

}

void TetrisFigure::render() const
{
	for (auto pBlock : m_blocks)
	{
		pBlock->render();
	}
}

void TetrisFigure::update(const double delta)
{
	for (auto pBlock : m_blocks)
	{
		pBlock->update(delta);
	}
	m_position = m_blocks[1]->getCurrentPosition();
}

void TetrisFigure::setSprite(const std::shared_ptr<RenderEngine::Sprite> pSprite)
{
	m_pSprite = pSprite;
	for (auto pBlock : m_blocks)
	{
		pBlock->setSprite(pSprite);
	}
}

void TetrisFigure::setVelocity(const glm::vec2 velocity)
{
	IGameObject::setVelocity(velocity);
	for (auto pBlock : m_blocks)
	{
		pBlock->setVelocity(velocity);
	}
}

void TetrisFigure::addVelocity(const glm::vec2 velocity)
{
	IGameObject::addVelocity(velocity);
	for (auto pBlock : m_blocks)
	{
		pBlock->addVelocity(velocity);
	}
}

void TetrisFigure::keyCallback(glm::vec2 velocity)
{
	for (auto pBlock : m_blocks)
	{
		pBlock->keyCallback(velocity);
	}
};

void TetrisFigure::blockStoppedCallback()
{	
	for (auto pBlock : m_blocks)
	{
		pBlock->setVelocity(glm::vec2(0, 0));
		m_position.y = (floor(m_position.y * m_size.y) + 1) / m_size.y;
		pBlock->getCurrentPosition().y = (floor(pBlock->getCurrentPosition().y * pBlock->getSize().y) + 1) / pBlock->getSize().y;
	}	
	if (m_blockStoppedCallback)
	{
		m_blockStoppedCallback();
		m_blockStoppedCallback = false;
	}
}

void TetrisFigure::AddState(std::vector<glm::vec2> figureState)
{
	if (figureState.size() != m_blocks.size())
	{
		std::cout << "state size < blocks count";
	}
	m_figureStates.emplace_back(figureState);
}

void TetrisFigure::rotate()
{

	if (m_figureStates.size() == 1) return;

	m_state++;
	if (m_state >= m_figureStates.size())
	{
		m_state = 0;
	}
	std::vector<glm::vec2> newState = m_figureStates[m_state];

	for (int i = 0; i < m_blocks.size(); i++)
	{
		auto block = m_blocks[i];
		block->getCurrentPosition() = m_position + newState[i];
		block->getCurrentPosition().y = (floor(block->getCurrentPosition().y / block->getSize().y) + 1) * block->getSize().y;
	}
}

void TetrisFigure::onBlockCollision(Physics::BoxCollider* collider)
{
	blockStoppedCallback();	
}