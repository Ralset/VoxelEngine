#pragma once

#include "Camera.h"
#include "core/Input.h"

#include <glm/glm.hpp>
#include <memory>

class Player{
    public:
        Player(glm::vec3 startLocation, const float speed, const float width, const float height);
        void Update();

        inline glm::mat4 getView() const { return m_camera->getView(m_Position); };
        inline glm::mat4 getProjection() const { return m_camera->getProjection(); };

        inline bool isKeyPressed(int key) const { return m_input->isKeyPressed(key); };
        inline void onKey(int key, int action) const { m_input->onKey(key, action); };
        inline void onCursorMove(double x, double y) const { m_input->onCursorMove(x, y); };

    private:
        const float m_speed;
        glm::vec3 m_Position;
        std::unique_ptr<Camera> m_camera;
        std::unique_ptr<Input> m_input;
};