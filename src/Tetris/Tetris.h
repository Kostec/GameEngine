#pragma once

#include <array>
#include <glm/vec2.hpp>
#include <memory>
#include "../Controller/IController.h"

#include "../System/Timer.h"

class Tank;
class TetrisLevel;
class TetrisBlock;
class TetrisFigure;
class ILevel;

class Tetris
{
public:
	enum class EGameState {
		Active, Pause
	};

	Tetris(const glm::vec2& widowSize);
	~Tetris();

	void render();
	void update(const double delta);
	void setKey(const int key, const int action);

	bool init();

	size_t getCurrentLevelWidth() const;
	size_t getCurrentLevelHeight() const;

	TetrisFigure* generateFigure();
	void spawnFigure();

private:

	IController m_controller;

	std::array<bool, 349> m_keys;

	glm::vec2 m_widowSize;
	EGameState m_CurrentGameState;

	std::shared_ptr<Tank> m_tank;
	std::shared_ptr<TetrisLevel> m_level;
	TetrisFigure* m_activeFigure;

	Timer m_updateTimer;

	double m_blockVelocity = 0.05;
	double m_maxBlockVelocity = 0.5;

	EGameState m_gameState;
};