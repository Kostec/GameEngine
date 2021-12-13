#pragma once

#include <vector>
#include <memory>
#include <glm/vec2.hpp>

class IGameObject;

class ILevel
{
public:
	static constexpr unsigned int BLOCK_SIZE = 16;

	virtual void render() const;
	virtual void update(const double delta);
	virtual size_t getLevelWidth() const;
	virtual size_t getLevelHeight() const;

	//virtual std::vector<std::shared_ptr<IGameObject>> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight);
	//std::vector<std::shared_ptr<IGameObject>> getObjects() { return m_mapObject; }
	virtual std::vector<IGameObject*> getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight);
	std::vector<IGameObject*> getObjects() { return m_mapObject; }

protected:
	//std::vector<std::shared_ptr<IGameObject>> m_mapObject;
	std::vector<IGameObject*> m_mapObject;

	size_t m_widthBlocks;
	size_t m_heightBlocks;
	unsigned int m_widthPixels;
	unsigned int m_heightPixels;
	double m_blockVelicity = -0.05;
};