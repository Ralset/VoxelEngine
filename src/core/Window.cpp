#include "core/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include<iostream>

Window::Window(int width, int height, const char* title) : m_width(width), m_height(height)
{    
    // Setuju minimalnu opengl verziju, ako je nema onda ce window automatski failovati da se napravi
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);
    if (!m_window){
        throw std::runtime_error("Failed to create a window");
    }

    glfwMakeContextCurrent(m_window);

    // VSYNC
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwGetFramebufferSize(m_window, &m_framebufferWidth, &m_framebufferHeight);
    glViewport(0, 0, m_framebufferWidth, m_framebufferHeight);
}

bool Window::shouldWindowClose(){
    return glfwWindowShouldClose(m_window);
}

void Window::swapBuffers(){
    glfwSwapBuffers(m_window);
}

void Window::resizeWindow(int width, int height)
{
    m_width=width;
    m_height=height;
    glfwGetFramebufferSize(m_window, &m_framebufferWidth, &m_framebufferHeight);
    glViewport(0, 0, m_width, m_height);
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
}