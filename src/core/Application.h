#pragma once

#include "Input.h"
#include "Window.h"

#include <memory>

class Application{
    public:
        Application();
        ~Application();
        void Run();
    private:
        static void resizeCallBack(GLFWwindow* window, int width, int height);
        static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
        std::unique_ptr<Window> m_window;
        Input m_input;
};