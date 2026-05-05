#include "Application.h"

#include "core/Window.h"
#include "graphics/Renderer.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <stdexcept>

Application::Application() {
    ASSERT(glfwInit());
    m_window = std::make_unique<Window>(800, 600, "VoxelGame");
    glfwSetWindowUserPointer(m_window->getWindow(), this);
    glfwSetFramebufferSizeCallback(m_window->getWindow(), resizeCallBack);
    glfwSetKeyCallback(m_window->getWindow(), keyCallBack);
    glfwSetCursorPosCallback(m_window->getWindow(), cursorPosCallback);
}

Application::~Application() {
    glfwTerminate();
}

void Application::resizeCallBack(GLFWwindow* window, int width, int height){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->m_window->resizeWindow(width, height);
}

void Application::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->m_input.onKey(key, action);
}

void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->m_input.onCursorMove(xpos, ypos);
}

void Application::Run()
{
    float points[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexBuffer vbo(points, 8 * sizeof(float));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    IndexBuffer ebo(indices, 6 * sizeof(unsigned int));

    Shader shader("assets/shaders/Vertex.shader", "assets/shaders/Fragment.shader");
    
    glm::mat4 transform = glm::mat4(1.0f);
    
    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    vbo.Unbind();
    ebo.Unbind();

    float increment = 0.01f;
    float r = 0.0f;

    while (!m_window->shouldWindowClose()&&!m_input.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        r+=increment;
        if(r>=1||r<=0){
            increment*=-1.0f;
        }
        m_input.update();
        if(m_input.isKeyHeld(GLFW_KEY_UP) && !m_input.isKeyHeld(GLFW_KEY_DOWN))
            transform = glm::translate(transform, glm::vec3(0, 0.01f, 0.0f));
        else if(m_input.isKeyHeld(GLFW_KEY_DOWN) && !m_input.isKeyHeld(GLFW_KEY_UP)) 
            transform = glm::translate(transform, glm::vec3(0, -0.01f, 0.0f));
        if(m_input.isKeyHeld(GLFW_KEY_LEFT) && !m_input.isKeyHeld(GLFW_KEY_RIGHT))
            transform = glm::translate(transform, glm::vec3(-0.01f, 0, 0.0f));
        else if(m_input.isKeyHeld(GLFW_KEY_RIGHT) && !m_input.isKeyHeld(GLFW_KEY_LEFT))
            transform = glm::translate(transform, glm::vec3(0.01f, 0, 0.0f));

        if(m_input.isKeyHeld(GLFW_KEY_W) && !m_input.isKeyHeld(GLFW_KEY_S))
            transform = glm::scale(transform, glm::vec3(1.01f, 1.01f, 1.01f));
        else if(m_input.isKeyHeld(GLFW_KEY_S) && !m_input.isKeyHeld(GLFW_KEY_W))
            transform = glm::scale(transform, glm::vec3(0.99f, 0.99f, 0.99f));
        //std::cout<<m_input.mousePosition.x<<' '<<m_input.mousePosition.y<<std::endl;
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        shader.use();
        shader.setUniform("u_Transform", transform);
        shader.setUniform("u_Color", glm::vec4(r, 0.3f, 0.8f, 1.0f));

        GLCall(glBindVertexArray(vao));
        ebo.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        m_window->swapBuffers();
        glfwPollEvents();
    }
}