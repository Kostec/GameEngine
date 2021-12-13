#pragma once

#include <vector>
#include <string>
#include <memory>
#include <glm/vec2.hpp>

#include "ILevel.h"

class IGameObject;

class Level : public ILevel
{
public: 

	static constexpr unsigned int BLOCK_SIZE = 16;

	Level(const std::vector<std::string>& levelDescription);
	size_t getLevelWidth() const;
	size_t getLevelHeight() const;

	const glm::ivec2& getPlayerRespawn_1() const { return m_playerRespawn_1; }
	const glm::ivec2& getPlayerRespawn_2() const { return m_playerRespawn_2; }
	const glm::ivec2& getEnemyRespawn_1() const { return m_enemyRespawn_1; }
	const glm::ivec2& getEnemyRespawn_2() const { return m_enemyRespawn_2; }
	const glm::ivec2& getEnemyRespawn_3() const { return m_enemyRespawn_3; }


private:

	glm::ivec2 m_playerRespawn_1;
	glm::ivec2 m_playerRespawn_2;
	glm::ivec2 m_enemyRespawn_1;
	glm::ivec2 m_enemyRespawn_2;
	glm::ivec2 m_enemyRespawn_3;
};