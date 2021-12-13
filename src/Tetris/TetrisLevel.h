#pragma once

#include "../Game/ILevel.h"
#include <glm/vec2.hpp>
#include <vector>
#include "../System/Timer.h"

class TetrisBlock;
class TetrisFigure;

namespace Physics{
	class BoxCollider;
}

class TetrisLevel : public ILevel
{

public:
	TetrisLevel();
	~TetrisLevel();
	
	void AddFigure(TetrisFigure* figure);

	void render() const override;
	void update(const double delta) override;

private:

	void checkLine();

	double m_time = 0;
	TetrisFigure* m_currentFigure;
};