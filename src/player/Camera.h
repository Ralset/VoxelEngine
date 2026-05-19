#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
    public:
        Camera(const glm::vec3 startPosition, const float sensitivity,const float fov, const float width, const float height, const float nearPlane, const float farPlane);
        void moveUp(const float speed);
        void moveDown(const float speed);
        void moveLeft(const float speed);
        void moveRight(const float speed);
        void moveForward(const float speed);
        void moveBackwards(const float speed);

        void changeRotation(const float xoffset, const float yoffset);

        inline glm::mat4 getView() const { return glm::lookAt(m_Position, m_Position + m_Front, glm::vec3(0,1,0)); };
        inline glm::mat4 getProjection() const { return m_Projection; };
    
    private:
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_FrontMovement;
        glm::mat4 m_Projection;
        float m_pitch;
        float m_yaw;
        float m_sensitivity;
};