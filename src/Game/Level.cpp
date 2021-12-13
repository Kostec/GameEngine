#include "Level.h"

//#include "GameObjects/IGameObject.h"
#include "GameObjects/BrickWall.h"
#include "GameObjects/Border.h"

#include "../Resources/Resourcemanager.h"

#include <iostream>
#include <algorithm>
#include <cmath>

std::shared_ptr<IGameObject> createGameObjectFromDescription(const char description, const glm::vec2& position, const glm::vec2& size, const float rotation)
{
	/*switch (description)
	{
	case '0':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("grass"), position, size, rotation, 0.f);
		break;
	case '1':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("ground"), position, size, rotation, 0.f);
		break;
	case '2':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("ground_grass"), position, size, rotation, 0.f);
		break;
	case '3':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("wood"), position, size, rotation, 0.f);
		break;
	case '4':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("brick"), position, size, rotation, 0.f);
		break;
	case 'G':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("beton"), position, size, rotation, 0.f);
		break;
	case 'H':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("beton1"), position, size, rotation, 0.f);
		break;
	case 'I':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("beton2"), position, size, rotation, 0.f);
		break;
	case 'J':
		return std::make_shared<BrickWall>(ResourceManager::getSprite("mramor"), position, size, rotation, 0.f);
		break;
	case 'D':
		return nullptr;
		break;
	default:
		std::cerr << "Unknown GameObject description " << description << std::endl;
		break;
	}*/

	return nullptr;
}

Level::Level(const std::vector<std::string>& levelDescription)
{
	if (levelDescription.empty())
	{
		std::cerr << "Empty level description" << std::endl;
		return;
	}

	m_widthBlocks = levelDescription[0].length();
	m_heightBlocks = levelDescription.size();
	m_widthPixels = m_widthBlocks * BLOCK_SIZE;
	m_heightPixels = m_heightBlocks * BLOCK_SIZE;

	m_playerRespawn_1 = { BLOCK_SIZE * (m_widthBlocks / 2 - 1), BLOCK_SIZE / 2};
	m_playerRespawn_2 = { BLOCK_SIZE * (m_widthBlocks / 2 + 3), BLOCK_SIZE / 2 };

	m_enemyRespawn_1 = { BLOCK_SIZE, BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn_2 = { BLOCK_SIZE * (m_widthBlocks / 2 + 1), BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };
	m_enemyRespawn_3 = { BLOCK_SIZE * m_widthBlocks, BLOCK_SIZE * m_heightBlocks - BLOCK_SIZE / 2 };

	m_mapObject.reserve(m_widthBlocks * m_heightBlocks + 4);

	unsigned int currentBottomOffset = static_cast<unsigned int> (BLOCK_SIZE * (m_heightBlocks - 1) + BLOCK_SIZE / 2.f);

	for (const std::string& currentRow : levelDescription)
	{
		unsigned int currentLeftOffset = BLOCK_SIZE;
		for (char currentElement : currentRow)
		{
			switch (currentElement)
			{
			case 'K':
				m_playerRespawn_1 = { currentLeftOffset, currentBottomOffset };
				m_mapObject.emplace_back(nullptr);
				break;
			case 'L':
				m_playerRespawn_2 = { currentLeftOffset, currentBottomOffset };
				m_mapObject.emplace_back(nullptr);
				break;
			case 'M':
				m_enemyRespawn_1 = { currentLeftOffset, currentBottomOffset };
				m_mapObject.emplace_back(nullptr);
				break;
			case 'N':
				m_enemyRespawn_2 = { currentLeftOffset, currentBottomOffset };
				m_mapObject.emplace_back(nullptr);
				break;
			case 'O':
				m_enemyRespawn_3 = { currentLeftOffset, currentBottomOffset };
				m_mapObject.emplace_back(nullptr);
				break;
			default:
				//m_mapObject.emplace_back(createGameObjectFromDescription(currentElement, glm::vec2(currentLeftOffset, currentBottomOffset), glm::vec2(BLOCK_SIZE, BLOCK_SIZE), 0));
				break;
			}
			currentLeftOffset += BLOCK_SIZE;
		}
		currentBottomOffset -= BLOCK_SIZE;
	}

	//// bottom border
	//m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, 0), glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0, 0.f));
	//// top border
	//m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2(BLOCK_SIZE, m_heightBlocks * BLOCK_SIZE + BLOCK_SIZE / 2.f), glm::vec2(m_widthBlocks * BLOCK_SIZE, BLOCK_SIZE / 2.f), 0, 0.f));
	//// left border
	//m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2(0.f, 0.f), glm::vec2(BLOCK_SIZE, (m_heightBlocks + 1) * BLOCK_SIZE), 0, 0.f));
	//// right border
	//m_mapObject.emplace_back(std::make_shared<Border>(glm::vec2((m_widthBlocks + 1) * BLOCK_SIZE, 0.f), glm::vec2(BLOCK_SIZE * 2.f, (m_heightBlocks + 1) * BLOCK_SIZE), 0, 0.f));
}

size_t Level::getLevelWidth() const
{
	return (m_widthBlocks + 3) * BLOCK_SIZE;
}

size_t Level::getLevelHeight() const
{
	return (m_heightBlocks + 1) * BLOCK_SIZE;
}
