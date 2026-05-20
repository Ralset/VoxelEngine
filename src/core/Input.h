#pragma once

struct GLFWwindow;

class Input{
    public:
        Input(const float width, const float height);
        void update();

        inline bool isKeyPressed(int key)  const { return  m_currentKeys[key] && !m_previousKeys[key]; };
        inline bool isKeyReleased(int key) const { return !m_currentKeys[key] &&  m_previousKeys[key]; };
        inline bool isKeyHeld(int key)     const { return  m_currentKeys[key]; };

        inline bool isLMBClicked()  const { return  m_LMB && !m_previousLMB; };
        inline bool isRMBClicked()  const { return  m_RMB && !m_previousRMB; };
        inline bool isLMBReleased() const { return !m_LMB &&  m_previousLMB; };
        inline bool isRMBReleased() const { return !m_RMB &&  m_previousRMB; };
        inline bool isLMBHeld()     const { return  m_LMB; };
        inline bool isRMBHeld()     const { return  m_RMB; };

        inline float getPitchChange() const { return m_pitchChange; };
        inline float getYawChange() const { return m_yawChange; };

        void onKey(int key, int action);
        void onCursorMove(double xpos, double ypos);
        void onMouseButtonClick(int button, int action);

    private:
        bool m_firstMove;
        bool m_LMB;
        bool m_previousLMB;
        bool m_RMB;
        bool m_previousRMB;
        bool m_currentKeys[350];
        bool m_previousKeys[350];
        float m_x;
        float m_y;
        float m_previousX;
        float m_previousY;
        float m_yawChange;
        float m_pitchChange;
};