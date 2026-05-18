#pragma once

struct GLFWwindow;

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
        inline float getPitch() const { return m_pitch; };
        inline float getYaw() const { return m_yaw; };

    private:
        bool m_currentKeys[350];
        bool m_previousKeys[350];
        float m_pitch;
        float m_yaw;
        float m_x;
        float m_y;
        const float m_mouseSensitivity = 0.1f;
        bool firstMouse;
};