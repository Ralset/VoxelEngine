#include "Application.h"

#include "core/Window.h"
#include "graphics/GLUtils.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Shader.h"
#include "graphics/VertexArray.h"
#include "graphics/VertexBufferLayout.h"
#include "graphics/Renderer.h"

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

        4, 5, 6, // back
        6, 7, 4,

        3, 2, 6, // top
        6, 7, 3,

        0, 1, 5, // bottom
        5, 4, 0,

        0, 3, 7, // left
        7, 4, 0,
        
        1, 2, 6, // right
        6, 5, 1
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

    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 cameraPosition(0.0f, 0.0f, 10.0f);
    glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraFront + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), 1280.0f / 720.0f, 0.1f, 100.0f);

    shader.Bind();
    shader.setUniform("u_Model", model);
    shader.setUniform("u_View", view);
    shader.setUniform("u_Projection", proj);
    shader.setUniform("u_Color", glm::vec4(0.1f, 0.3f, 0.8f, 1.0f));
    shader.Unbind();

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    const float cameraSpeed = 0.1f;

    while (!m_window->shouldWindowClose()&&!m_input.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        m_input.update();
        renderer.Clear();

        glm::vec3 direction;
        direction.x = cos(glm::radians(m_input.getYaw())) * cos(glm::radians(m_input.getPitch()));
        direction.y = 0;
        direction.z = sin(glm::radians(m_input.getYaw())) * cos(glm::radians(m_input.getPitch()));
        cameraFront = glm::normalize(direction);

        if(m_input.isKeyHeld(GLFW_KEY_W)) cameraPosition += cameraSpeed * cameraFront;
        if(m_input.isKeyHeld(GLFW_KEY_S)) cameraPosition -= cameraSpeed * cameraFront;
        if(m_input.isKeyHeld(GLFW_KEY_A)) cameraPosition -= cameraSpeed * glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
        if(m_input.isKeyHeld(GLFW_KEY_D)) cameraPosition += cameraSpeed * glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f)));
        if(m_input.isKeyHeld(GLFW_KEY_SPACE)) cameraPosition += cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
        if(m_input.isKeyHeld(GLFW_KEY_LEFT_SHIFT)) cameraPosition -= cameraSpeed * glm::vec3(0.0f, 1.0f, 0.0f);

        direction.y = sin(glm::radians(m_input.getPitch()));
        cameraFront = glm::normalize(direction);

        std::cout<<m_input.getPitch()<<' '<<m_input.getYaw()<<'\n';


        shader.Bind();
        view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, glm::vec3(0.0, 1.0, 0.0));
        shader.setUniform("u_View", view);

        for(int i=0;i<4;i++){
            shader.setUniform("u_Model", glm::translate(model, blocks[i]));
            renderer.Draw(vao, ebo, shader);
        }
        

        m_window->swapBuffers();
        glfwPollEvents();
    }
}