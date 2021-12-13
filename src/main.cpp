
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>

#include "Renderer/ShaderProgram.h"
#include "Renderer/Texture2D.h"
#include "Renderer/Sprite.h"
#include "Renderer/Renderer.h"
#include "Resources/Resourcemanager.h"

#include "Physics/PhysicsEngine.h"

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "Game/Game.h"

#include "Tetris/Tetris.h"

glm::vec2 g_widowSize(13 * 16, 14 * 16);
std::unique_ptr<Tetris> g_game = std::make_unique<Tetris>(g_widowSize);
GLFWwindow* pwindow;

void closeWindow()
{
    glfwSetWindowShouldClose(pwindow, GL_TRUE);
}

void glfwWindowResizeCallback(GLFWwindow* pWindow, int width, int height)
{

    g_widowSize.x = width;
    g_widowSize.y = height;

    //const float map_aspect_ratio = static_cast<float>(13) / 14;

    const float map_aspect_ratio = static_cast<float>(g_game->getCurrentLevelWidth())/ g_game->getCurrentLevelHeight();

    unsigned int viewPortWidth = g_widowSize.x;
    unsigned int viewPortHeight = g_widowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(g_widowSize.x) / g_widowSize.y > map_aspect_ratio)
    {
        viewPortWidth = static_cast<unsigned int>(g_widowSize.y * map_aspect_ratio);
        viewPortLeftOffset = (g_widowSize.x - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(g_widowSize.x / map_aspect_ratio);
        viewPortBottomOffset = (g_widowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::setVieport(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
}

void glfwWindowCloseCallback(GLFWwindow* pWindow)
{
    std::cout << "Window close callback" << std::endl;

    ResourceManager::unloadAllResources();
}

void glfwKeyCallback(GLFWwindow* pwindow, int key, int scancode, int action, int mode)
{    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pwindow, GL_TRUE);
    }

    g_game->setKey(key, action);
}

int main(int argc, char** argv)
{  
    //ALCdevice* device = alcOpenDevice(NULL);

    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "GLFW initialization error" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    pwindow = glfwCreateWindow(g_widowSize.x, g_widowSize.y, "Game", nullptr, nullptr);
    if (!pwindow)
    {
        glfwTerminate();
        std::cout << "Create window error" << std::endl;
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(pwindow);
	
	if (!gladLoadGL())
	{
		std::cout << "Can't load GLAD!" << std::endl;
		return -1;
	}
	
    std::cout << "OpenGL " << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;
    std::cout << "OpenGL " << "OpenGL version " << RenderEngine::Renderer::getVersionStr() << std::endl;
	

    glfwSetWindowSizeCallback(pwindow, glfwWindowResizeCallback);
    glfwSetKeyCallback(pwindow, glfwKeyCallback);
    
    {
        ResourceManager::setExecutablePath(argv[0]);
        Physics::PhysicsEngine::init();
        g_game->init();

        auto lastTime = std::chrono::high_resolution_clock::now();

        glfwSetWindowCloseCallback(pwindow, glfwWindowCloseCallback);
        glfwSetWindowSize(pwindow, static_cast<int>(3 * g_game->getCurrentLevelWidth()), static_cast<int>(3 * g_game->getCurrentLevelHeight()));

        RenderEngine::Renderer::setClearColor(0, 0, 0, 1);
        RenderEngine::Renderer::setDepth(true);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(pwindow))
        {
            glfwPollEvents();

            auto currentTime = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration<double, std::milli>(currentTime - lastTime).count();
            lastTime = currentTime;

            g_game->update(duration);
            Physics::PhysicsEngine::update(duration);
            RenderEngine::Renderer::clear();
            g_game->render();

            glfwSwapBuffers(pwindow);            
        }

        ResourceManager::unloadAllResources();
    }

    g_game = nullptr;
    glfwTerminate();
    return 0;
}
