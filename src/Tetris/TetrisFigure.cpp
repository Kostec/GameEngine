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
	TetrisBlock* block = new TetrisBlock(blockCoors + m_kinematic.getPoition(), 0);
	block->setBlockStoppedCallBack([&]() {blockStoppedCallback(); });
	m_kinematic.onVelocityChanged += METHOD_HANDLER(block->getKinematic(), Kinematic::setCurrentVelocity);

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
	IGameObject::update(delta);
	for (auto pBlock : m_blocks)
	{
		pBlock->update(delta);
	}
}

void TetrisFigure::setSprite(const std::shared_ptr<RenderEngine::Sprite> pSprite)
{
	m_pSprite = pSprite;
	for (auto pBlock : m_blocks)
	{
		pBlock->setSprite(pSprite);
	}
}

void TetrisFigure::keyCallback(glm::vec2 velocity)
{
	m_kinematic.setCurrentVelocity(velocity);
	for (auto pBlock : m_blocks)
	{
		pBlock->keyCallback(velocity);
	}
};

void TetrisFigure::blockStoppedCallback()
{	
	m_kinematic.setCurrentVelocity(glm::vec2(0));
	for (auto pBlock : m_blocks)
	{
		pBlock->getKinematic().setCurrentVelocity(glm::vec2(0, 0));
		m_kinematic.getCurrentPoition().y = (floor(m_kinematic.getCurrentPoition().y / m_size.y) + 1) * m_size.y;
		pBlock->getKinematic().getCurrentPoition().y = (floor(pBlock->getKinematic().getCurrentPoition().y / pBlock->getSize().y) + 1) * pBlock->getSize().y;
	}	
	if (m_blockStoppedCallback)
	{
		m_blockStoppedCallback();
		m_blockStoppedCallback = nullptr;
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
		block->getKinematic().getCurrentPoition() = m_kinematic.getCurrentPoition() + newState[i];
		block->getKinematic().getCurrentPoition().y = (floor(block->getKinematic().getCurrentPoition().y / block->getSize().y) + 1) * block->getSize().y;
	}
}

void TetrisFigure::onBlockCollision(Physics::BoxCollider* collider, glm::vec2 collisionSide)
{
	blockStoppedCallback();	
}