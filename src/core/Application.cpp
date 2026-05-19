#include "Application.h"

#include "core/Window.h"
#include "graphics/GLUtils.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/Renderer.h"
#include "player/Player.h"
#include "world/Chunk.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <stdexcept>

Application::Application() {
    ASSERT(glfwInit());
    m_window = std::make_unique<Window>(1280, 720, "VoxelGame");
    glfwSetFramebufferSizeCallback(m_window->getWindow(), resizeCallBack);
    glfwSetKeyCallback(m_window->getWindow(), keyCallBack);
    glfwSetCursorPosCallback(m_window->getWindow(), cursorPosCallback);
    glfwSetInputMode(m_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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


void Application::Run()
{
    float points[24] = {
        -0.5f, -0.5f, 0.5f, // dole levo front
        0.5f, -0.5f, 0.5f, // dole desno front
        0.5f, 0.5f, 0.5f,  // gore desno front
        -0.5f, 0.5f, 0.5f, // gore levo  front

        -0.5f, -0.5f, -0.5f, // dole levo back
        0.5f, -0.5f, -0.5f, // dole desno back
        0.5f, 0.5f, -0.5f,  // gore desno back
        -0.5f, 0.5f, -0.5f, // gore levo  back
    };

    unsigned int indices[36] = {
        0, 1, 2, // front 
        2, 3, 0, 

        6, 5, 4, // back
        4, 7, 6,

        3, 2, 6, // top
        6, 7, 3,

        5, 1, 0, // bottom
        0, 4, 5,

        0, 3, 7, // left
        7, 4, 0,

        6, 2, 1, // right
        1, 5, 6
    };

    const glm::vec3 blocks[4] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 5.0f, 1.0f),
        glm::vec3(2.0f, 2.0f, -2.0f),
        glm::vec3(-4.0f, 1.0f, 3.0f)
    };

    VertexBuffer vbo(points, 24 * sizeof(float));
    IndexBuffer ebo(indices, 36 * sizeof(unsigned int), 36);

    VertexArray vao;
    VertexBufferLayout layout;
    layout.Push<float>(3);
    vao.AddBuffer(vbo, layout);

    Shader shader("assets/shaders/Vertex.shader", "assets/shaders/Fragment.shader");
        
    shader.Unbind();
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    Renderer renderer;
    Player player(glm::vec3(0.0f, 0.0f, -2.0f), 0.1f, m_window->getWidth(), m_window->getHeight());
    m_userData = { this, &player }; 
    glfwSetWindowUserPointer(m_window->getWindow(), &m_userData);
    
    glm::mat4 model(1.0f);

    shader.Bind();
    shader.setUniform("u_Color", glm::vec4(0.1f, 0.3f, 0.8f, 1.0f));
    shader.Unbind();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!m_window->shouldWindowClose() && !player.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        renderer.Clear();
        player.Update();

        shader.Bind();
        shader.setUniform("u_View", player.getView());
        shader.setUniform("u_Projection", player.getProjection());

        for(int i=0;i<4;i++){
            shader.setUniform("u_Model", glm::translate(model, blocks[i]));
            renderer.Draw(vao, ebo, shader);
        }

        m_window->swapBuffers();
        glfwPollEvents();
    }
}