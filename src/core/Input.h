#pragma once

struct GLFWwindow;

struct vec2 {
    double x,y;
};

class Input{
    public:
        Input();
        void BindWindow(GLFWwindow* window);
        void update();
        bool isKeyPressed(int key) const;
        bool isKeyHeld(int key) const;
        bool isKeyReleased(int key) const;
        void onKey(int key, int action);
        void onCursorMove(double xpos, double ypos);
        vec2 mousePosition;

    private:
        bool m_currentKeys[350];
        bool m_previousKeys[350];
};