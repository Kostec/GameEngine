#include "Game.h"

#include<iostream>

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Resources/Resourcemanager.h"
#include "../Physics/PhysicsEngine.h"

#include "GameObjects/Tank.h"
#include "Level.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "../Controller/CustomKey.h"

Game::Game(const glm::vec2& widowSize)
	: m_CurrentGameState(EGameState::Active),
    m_widowSize(widowSize)
{
	m_keys.fill(false);
    
    m_controller.setKey("Up", new CustomKey(GLFW_KEY_W, [&](bool value) { if (m_tank) m_tank->movingKeyCallback(Tank::EOrientation::Top, value ? glm::vec2(0, m_tank->getMaxVelocity()) : glm::vec2(0)); }));
    m_controller.setKey("Left", new CustomKey(GLFW_KEY_A, [&](bool value) { if (m_tank) m_tank->movingKeyCallback(Tank::EOrientation::Left, value ? glm::vec2(-m_tank->getMaxVelocity(), 0) : glm::vec2(0)); }));
    m_controller.setKey("Down", new CustomKey(GLFW_KEY_S, [&](bool value) { if (m_tank) m_tank->movingKeyCallback(Tank::EOrientation::Bottom, value ? glm::vec2(0, -m_tank->getMaxVelocity()) : glm::vec2(0)); }));
    m_controller.setKey("Right", new CustomKey(GLFW_KEY_D, [&](bool value) { if (m_tank) m_tank->movingKeyCallback(Tank::EOrientation::Right, value ? glm::vec2(m_tank->getMaxVelocity(), 0) : glm::vec2(0)); }));
}
	
Game::~Game()
{
    
}

void Game::render()
{
    if (m_level)
    {
        m_level->render();
    }

    if (m_tank)
    {
        m_tank->render();
    }
}

void Game::update(const double delta)
{
    if (m_level)
    {
        m_level->update(delta);
    }

    if (m_tank)
    {
        m_tank->update(delta);
    }
}

void Game::setKey(const int key, const int action)
{
    m_keys[key] = action;
    m_controller.actionKey(key, action);
}

bool Game::init()
{
    ResourceManager::loadJSONResources("res/resources.json");

    auto pSpriteShaderprogram = ResourceManager::getShaderProgram("SpriteShader");
    if (!pSpriteShaderprogram)
    {
        std::cerr << "Can't find shader program " << "SpriteShader" << std::endl;
        return false;
    }

    auto pTanksTextureAtlas = ResourceManager::getTexture("TanksTextureAtlas");
    if (!pTanksTextureAtlas)
    {
        std::cerr << "Can't find shader program " << "TanksTextureAtlas" << std::endl;
        return false;
    }


    m_level = std::make_shared<Level>(ResourceManager::getlevels()[0]);
    m_widowSize.x = static_cast<int>(m_level->getLevelWidth());
    m_widowSize.y = static_cast<int>(m_level->getLevelHeight());
    Physics::PhysicsEngine::setCurrentLevel(m_level);

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_widowSize.x), 0.f, static_cast<float>(m_widowSize.y), -100.f, 100.f);
    pSpriteShaderprogram->use();
    pSpriteShaderprogram->setInt("tex", GL_TEXTURE0);
    pSpriteShaderprogram->setMatrix4("projectionMat", projectionMatrix);

    m_tank = std::make_shared<Tank>(0.05, m_level->getPlayerRespawn_1(), glm::vec2(Level::BLOCK_SIZE, Level::BLOCK_SIZE), 1.f);
    Physics::PhysicsEngine::addDynamicGameObject(m_tank);

	return true;
}

size_t Game::getCurrentLevelWidth() const
{
    return m_level->getLevelWidth();
}

size_t Game::getCurrentLevelHeight() const
{
    return m_level->getLevelHeight();
}