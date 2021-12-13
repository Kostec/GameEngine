#pragma once

#include "ILevel.h"
#include "GameObjects/IGameObject.h"
#include <algorithm>
#include <cmath>

void ILevel::render() const
{
	for (const auto& currentmapObject : m_mapObject)
	{
		if (currentmapObject)
		{
			currentmapObject->render();
		}
	}
}

void ILevel::update(const double delta)
{
	for (const auto& currentmapObject : m_mapObject)
	{
		if (currentmapObject)
		{
			currentmapObject->update(delta);
		}
	}
}

size_t ILevel::getLevelWidth() const
{
	return m_widthPixels;
}

size_t ILevel::getLevelHeight() const
{
	return m_heightPixels;
}

std::vector<IGameObject*> ILevel::getObjectsInArea(const glm::vec2& bottomLeft, const glm::vec2& topRight)
{
	std::vector<IGameObject*> output;
	output.reserve(9);

	glm::vec2 bottomLeft_converted(std::clamp(bottomLeft.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_heightPixels - bottomLeft.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));

	glm::vec2 topRight_converted(std::clamp(topRight.x - BLOCK_SIZE, 0.f, static_cast<float>(m_widthPixels)),
		std::clamp(m_heightPixels - topRight.y + BLOCK_SIZE / 2, 0.f, static_cast<float>(m_heightPixels)));

	size_t startX = static_cast<size_t>(floor(bottomLeft_converted.x / BLOCK_SIZE));
	size_t endX = static_cast<size_t>(ceil(topRight_converted.x / BLOCK_SIZE));

	size_t startY = static_cast<size_t>(floor(topRight_converted.y / BLOCK_SIZE));
	size_t endY = static_cast<size_t>(ceil(bottomLeft_converted.y / BLOCK_SIZE));

	for (size_t currentColumn = startX; currentColumn < endX; ++currentColumn)
	{
		for (size_t currentRow = startY; currentRow < endY; ++currentRow)
		{
			auto currentObject = m_mapObject[currentRow * m_widthBlocks + currentColumn];
			if (currentObject)
			{
				output.push_back(currentObject);
			}
		}
	}

	// Границы карты
	if (endX >= m_widthBlocks)
	{
		output.push_back(m_mapObject[m_mapObject.size() - 1]);
	}
	if (startX <= 1)
	{
		output.push_back(m_mapObject[m_mapObject.size() - 2]);
	}
	if (startY >= m_heightBlocks)
	{
		output.push_back(m_mapObject[m_mapObject.size() - 3]);
	}
	if (endY >= m_heightBlocks)
	{
		output.push_back(m_mapObject[m_mapObject.size() - 4]);
	}
	return output;
}