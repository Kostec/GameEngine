#include "TetrisLevel.h"
#include "TetrisBlock.h"
#include "TetrisFigure.h"

#include "../Physics/PhysicsEngine.h"
#include "../Physics/Collider.h"
#include "../Game/GameObjects/Border.h"

#include "../Resources/Resourcemanager.h"

#include <iostream>
#include <algorithm>
#include <typeinfo>

TetrisLevel::TetrisLevel()
	:m_currentFigure(nullptr)
{

	m_widthBlocks = 15;
	m_heightBlocks = 9;

	m_heightPixels = TETRIS_BLOCK_SIZE * m_widthBlocks;
	m_widthPixels = TETRIS_BLOCK_SIZE * m_heightBlocks;

	m_mapObject.emplace_back(new Border(glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(m_widthPixels + TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE), 0, 0.f));
}

TetrisLevel::~TetrisLevel()
{
	m_mapObject.clear();
}

void TetrisLevel::AddFigure(TetrisFigure* figure)
{
	if (m_currentFigure)
	{
		auto blocks = m_currentFigure->getBlocks();
		m_mapObject.insert(m_mapObject.end(), blocks.begin(), blocks.end());
		checkLine();
	}
	m_currentFigure = figure;
}

void TetrisLevel::render() const
{
	ILevel::render();
	m_currentFigure->render();
}

void TetrisLevel::update(const double delta)
{
	if (m_currentFigure)
	{
		std::vector<Physics::BoxCollider> objectColliders = m_currentFigure->getObjectColliders();
		for (auto& collider : objectColliders)
		{
			collider.checkCollision(m_mapObject);
		}
	}
	ILevel::update(delta);
	m_currentFigure->update(delta);
}

void TetrisLevel::checkLine()
{
	for (int i = m_heightBlocks; i > 0; i--)
	{
		int figurePositionY = i * TETRIS_BLOCK_SIZE;

		int count = std::count_if(m_mapObject.begin(), m_mapObject.end(), [&](IGameObject* obj) {
			return abs(obj->getKinematic().getCurrentPosition().y - figurePositionY) < TETRIS_BLOCK_SIZE / 2; });
		if (count >= 9)
		{
			auto removeIt = std::remove_if(m_mapObject.begin(), m_mapObject.end(), [&](IGameObject* obj) { return abs(obj->getKinematic().getCurrentPosition().y - figurePositionY) < 1; });
			m_mapObject.erase(removeIt, m_mapObject.end());

			for (auto& obj : m_mapObject)
			{
				if (obj->getKinematic().getCurrentPosition().y > figurePositionY)
				{ 
					obj->getKinematic().getCurrentPosition().y = floor((obj->getKinematic().getCurrentPosition().y - TETRIS_BLOCK_SIZE) * TETRIS_BLOCK_SIZE) / TETRIS_BLOCK_SIZE;
				}
			}
		}
	}
}
