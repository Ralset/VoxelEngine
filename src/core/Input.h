#pragma once

struct GLFWwindow;

class Input{
    public:
        Input(const float width, const float height);
        void BindWindow(GLFWwindow* window);
        void update();
        bool isKeyPressed(int key) const;
        bool isKeyHeld(int key) const;
        bool isKeyReleased(int key) const;
        void onKey(int key, int action);
        void onCursorMove(double xpos, double ypos);
        inline float getPitchChange() const { return m_pitchChange; };
        inline float getYawChange() const { return m_yawChange; };

    private:
        bool m_firstMove;
        bool m_currentKeys[350];
        bool m_previousKeys[350];
        float m_x;
        float m_y;
        float m_previousX;
        float m_previousY;
        float m_yawChange;
        float m_pitchChange;
};