#pragma once

#include <array>
#include <glm/vec2.hpp>
#include <memory>
#include "../Controller/IController.h"

class Tank;
class Level;

class Game
{
public:
	Game(const glm::vec2& widowSize);
	~Game();

	void render();
	void update(const double delta);
	void setKey(const int key, const int action);

	bool init();

	size_t getCurrentLevelWidth() const;
	size_t getCurrentLevelHeight() const;

private:
	IController m_controller;

	std::array<bool, 349> m_keys;

	enum class EGameState {
		Active, Pause
	};

	glm::vec2 m_widowSize;
	EGameState m_CurrentGameState;

	std::shared_ptr<Tank> m_tank;
	std::shared_ptr<Level> m_level;

};