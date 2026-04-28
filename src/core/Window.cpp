#include "core/Window.h"
#include <iostream>

Window::Window(int width, int height, const char* title) : m_width(width), m_height(height)
{
    if (!glfwInit()){
        std::cerr<<"ERROR in initializing glfw"<<std::endl;
        return;
    }
    
    // Setuju minimalnu opengl verziju, ako je nema onda ce window automatski failovati da se napravi
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    
    m_window = glfwCreateWindow(m_width, m_height, title, NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return;
    }

}

GLFWwindow* Window::get_window() {
    return m_window;
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}