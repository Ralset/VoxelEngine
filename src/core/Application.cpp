#include "core/Application.h"

#include "graphics/Shader.h"

#include "graphics/GLUtils.h"
#include "core/Window.h"
#include "graphics/Renderer.h"
#include "player/Player.h"
#include "world/World.h"
#include "world/Chunk.h"

#include <GLFW/glfw3.h>

Application::Application() {
    ASSERT(glfwInit());
    m_window = std::make_unique<Window>(1280, 720, "VoxelGame");
    glfwSetFramebufferSizeCallback(m_window->getWindow(), resizeCallBack);
    glfwSetKeyCallback(m_window->getWindow(), keyCallBack);
    glfwSetCursorPosCallback(m_window->getWindow(), cursorPosCallback);
    glfwSetMouseButtonCallback(m_window->getWindow(), mouseButtonCallback);
}

Application::~Application() {
    glfwTerminate();
}

void Application::resizeCallBack(GLFWwindow* window, int width, int height) {
    auto* data = static_cast<WindowUserData*>(glfwGetWindowUserPointer(window));
    data->app->m_window->resizeWindow(width, height);
}
void Application::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* data = static_cast<WindowUserData*>(glfwGetWindowUserPointer(window));
    data->player->onKey(key, action);
}
void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* data = static_cast<WindowUserData*>(glfwGetWindowUserPointer(window));
    data->player->onCursorMove(xpos, ypos);
}
void Application::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    auto* data = static_cast<WindowUserData*>(glfwGetWindowUserPointer(window));
    data->player->onMouseButtonClick(button, action);
}

void Application::Run()
{
    Renderer renderer;

    World world(16);

    Player player(&world, glm::vec3(0.0f, 4.0f, 0.0f), 1.8f, 0.1f, m_window->getWidth(), m_window->getHeight());
    m_userData = { this, &player };
    glfwSetWindowUserPointer(m_window->getWindow(), &m_userData);

    while (!m_window->shouldWindowClose() && !player.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        renderer.Clear();
        player.Update();

        renderer.m_shader->Bind();
        renderer.m_shader->setUniform("u_View", player.getView());
        renderer.m_shader->setUniform("u_Projection", player.getProjection());
        renderer.m_shader->setUniform("u_Color", glm::vec4(0.1f, 0.3f, 0.8f, 1.0f));

        world.forEachChunk([&](const Chunk& chunk){
            renderer.m_shader->setUniform("u_Model", chunk.getModel());
            renderer.Draw(chunk.getVAO(), chunk.getEBO());
        });

        m_window->swapBuffers();
        glfwPollEvents();
    }
}