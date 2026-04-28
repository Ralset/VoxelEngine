#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        GLFWwindow* get_window();

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
};