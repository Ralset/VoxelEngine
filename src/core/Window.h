#pragma once

struct GLFWwindow;

class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        void swapBuffers();
        bool shouldWindowClose();

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
};