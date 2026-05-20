#pragma once

#include "Camera.h"
#include "core/Input.h"

#include <glm/glm.hpp>
#include <memory>

class World;

class Player{
    public:
        Player(World* world,glm::vec3 startLocation, const float playerHeight, const float speed, const float width, const float height);
        void Update();

        inline glm::mat4 getView() const { return m_camera->getView(m_Position + glm::vec3(0.0f, m_playerHeight, 0.0f)); };
        inline glm::mat4 getProjection() const { return m_camera->getProjection(); };

        inline bool isKeyPressed(int key) const { return m_input->isKeyPressed(key); };
        inline void onKey(int key, int action) const { m_input->onKey(key, action); };
        inline void onCursorMove(double x, double y) const { m_input->onCursorMove(x, y); };
        inline void onMouseButtonClick(int button, int action) const { m_input->onMouseButtonClick(button, action); };

    private:
        const float m_speed;
        const float m_playerHeight;
        glm::vec3 m_Position;
        std::unique_ptr<Camera> m_camera;
        std::unique_ptr<Input> m_input;
        World* currentWorld;

        void inputUpdate();
};