#pragma once

struct GLFWwindow;

class Window {
    public:
        Window(int width, int height, const char* title);
        ~Window();
        void swapBuffers();
        bool shouldWindowClose();
        void resizeWindow(int width, int height);
        inline GLFWwindow* getWindow() const {return m_window; };
        inline int getWidth() const { return m_width; };
        inline int getHeight() const { return m_height; };

    private:
        GLFWwindow* m_window;
        int m_width;
        int m_height;
        int m_framebufferWidth;
        int m_framebufferHeight;
};