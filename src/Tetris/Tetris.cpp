#include "Tetris.h"

#include <iostream>
#include <math.h>
#include <ctime>
#include <cstdlib>

#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Resources/Resourcemanager.h"
#include "../Physics/PhysicsEngine.h"

#include "TetrisLevel.h"
#include "TetrisBlock.h"
#include "TetrisFigure.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "../Controller/CustomKey.h"

Tetris::Tetris(const glm::vec2& widowSize)
	: m_CurrentGameState(EGameState::Active),
    m_widowSize(widowSize),
    m_activeFigure(nullptr),
    m_gameState(Tetris::EGameState::Active)
{
    m_keys.fill(false);

    m_controller.setKey("Left", new CustomKey(GLFW_KEY_A, [&](bool value) { if (m_activeFigure) m_activeFigure->keyCallback(value ? glm::vec2(-m_blockVelocity, -m_blockVelocity) : glm::vec2(0, -m_blockVelocity)); }));
    m_controller.setKey("Right", new CustomKey(GLFW_KEY_D, [&](bool value) { if (m_activeFigure) m_activeFigure->keyCallback(value ? glm::vec2(m_blockVelocity, -m_blockVelocity) : glm::vec2(0, -m_blockVelocity)); }));
    m_controller.setKey("Down", new CustomKey(GLFW_KEY_S, [&](bool value) { if (m_activeFigure) m_activeFigure->keyCallback(value ? glm::vec2(0, -m_maxBlockVelocity) : glm::vec2(0, -m_blockVelocity)); }));
    m_controller.setKey("Up", new CustomKey(GLFW_KEY_W, [&](bool value) { if (value && m_activeFigure) m_activeFigure->rotate(); }));
}
	
Tetris::~Tetris()
{
    
}

void Tetris::render()
{
    if (m_level)
    {
        m_level->render();
    }
}

void Tetris::update(const double delta)
{
    if (m_gameState == Tetris::EGameState::Pause)
        return;

    if (m_level)
    {
        m_level->update(delta);
    }

    Physics::PhysicsEngine::update(delta);
}

void Tetris::setKey(const int key, const int action)
{
    m_keys[key] = action;
    m_controller.actionKey(key, action);
}

bool Tetris::init()
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

    m_level = std::make_shared<TetrisLevel>();
    m_widowSize.x = static_cast<int>(m_level->getLevelWidth());
    m_widowSize.y = static_cast<int>(m_level->getLevelHeight());
    Physics::PhysicsEngine::setCurrentLevel(m_level);

    spawnFigure();

    glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_widowSize.x), 0.f, static_cast<float>(m_widowSize.y), -100.f, 100.f);
    pSpriteShaderprogram->use();
    pSpriteShaderprogram->setInt("tex", GL_TEXTURE0);
    pSpriteShaderprogram->setMatrix4("projectionMat", projectionMatrix);

	return true;
}

size_t Tetris::getCurrentLevelWidth() const
{
    return m_level->getLevelWidth();
}

size_t Tetris::getCurrentLevelHeight() const
{
    return m_level->getLevelHeight();
}

TetrisFigure* Tetris::generateFigure()
{
    srand(time(0));
    TetrisFigure* newFigure = nullptr;
    int figureType = rand() % 5;

    //figureType = 1;

    glm::vec2 spawnPoint = glm::vec2(floor(m_widowSize.x / TETRIS_BLOCK_SIZE / 2) * TETRIS_BLOCK_SIZE, m_widowSize.y - TETRIS_BLOCK_SIZE);

    switch (figureType)
    {
    case 0: // I
    {
        std::vector<glm::vec2> blockCoors{
            glm::vec2(TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE), glm::vec2(TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE * 2)
        };
        newFigure = new TetrisFigure(spawnPoint, blockCoors);
        newFigure->AddState({ glm::vec2(0), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(TETRIS_BLOCK_SIZE * 2, 0), glm::vec2(TETRIS_BLOCK_SIZE * 3, 0) });
        break;
    }
    case 1: // O
    {
        std::vector<glm::vec2> blockCoors{
            glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(-TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE), glm::vec2(0, -TETRIS_BLOCK_SIZE)
        };
        newFigure = new TetrisFigure(spawnPoint, blockCoors);
        break;
    }
    case 2: // L
    {
        std::vector<glm::vec2> blockCoors{
            glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE)
        };
        newFigure = new TetrisFigure(spawnPoint, blockCoors);

        newFigure->AddState({ glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(-TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(-TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE) });
        break;
    }
    case 3: // J
    {
        std::vector<glm::vec2> blockCoors{
            glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(-TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE)
        };
        newFigure = new TetrisFigure(spawnPoint, blockCoors);

        newFigure->AddState({ glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(-TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE) });
        break;
    }

    case 4: // S
    {
        std::vector<glm::vec2> blockCoors{
            glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE)
        };
        newFigure = new TetrisFigure(spawnPoint, blockCoors);

        newFigure->AddState({ glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(-TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(-TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE) });
        break;
    }

    case 5: // Z
    {
        std::vector<glm::vec2> blockCoors{
            glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(-TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE)
        };
        newFigure = new TetrisFigure(spawnPoint, blockCoors);

        newFigure->AddState({ glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(TETRIS_BLOCK_SIZE, TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(-TETRIS_BLOCK_SIZE, -TETRIS_BLOCK_SIZE) });
        break;
    }

    case 6: // T
    {
        std::vector<glm::vec2> blockCoors{
            glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(0, TETRIS_BLOCK_SIZE)
        };
        newFigure = new TetrisFigure(spawnPoint, blockCoors);

        newFigure->AddState({ glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(TETRIS_BLOCK_SIZE, 0) });
        newFigure->AddState({ glm::vec2(TETRIS_BLOCK_SIZE, 0), glm::vec2(0, 0), glm::vec2(-TETRIS_BLOCK_SIZE, 0), glm::vec2(0, -TETRIS_BLOCK_SIZE) });
        newFigure->AddState({ glm::vec2(0, -TETRIS_BLOCK_SIZE), glm::vec2(0, 0), glm::vec2(0, TETRIS_BLOCK_SIZE), glm::vec2(-TETRIS_BLOCK_SIZE, 0) });
        break;
    }

    }

    return newFigure;
}

void Tetris::spawnFigure()
{
    m_activeFigure = generateFigure();

    m_activeFigure->setSprite(ResourceManager::getSprite("grass"));
    m_activeFigure->getKinematic().setCurrentVelocity(glm::vec2(0.f, -m_blockVelocity));
    //m_activeFigure->getKinematic().setCurrentAcceleration(glm::vec2(0.f, -1e-5f));

    m_activeFigure->setBlockStoppedCallBack([&]() {
        spawnFigure();
        });

    m_level->AddFigure(m_activeFigure);
}