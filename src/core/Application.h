#pragma once

#include "core/Window.h"
#include <memory>

struct GLFWwindow;
class Player;
class Application;

struct WindowUserData {
    Application* app;
    Player* player;
};

class Application{
    public:
        Application();
        ~Application();
        void Run();
    private:
        static void resizeCallBack(GLFWwindow* window, int width, int height);
        static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

        std::unique_ptr<Window> m_window;
        WindowUserData m_userData;
};