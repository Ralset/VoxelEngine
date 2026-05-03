#pragma once

struct GLFWwindow;

class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        void swapBuffers();
        bool shouldWindowClose();
        void resizeWindow(int width, int height);
        inline GLFWwindow* getWindow() const {return m_window;} 

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
};