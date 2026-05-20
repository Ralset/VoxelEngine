#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
    public:
        Camera(const float sensitivity,const float fov, const float width, const float height, const float nearPlane, const float farPlane);

        void changeRotation(const float xoffset, const float yoffset);

        inline glm::vec3 getDirection() const { return m_Front; };
        inline glm::vec3 getMovDireciton() const { return m_FrontMovement; };
        inline glm::mat4 getView(glm::vec3 position) const { return glm::lookAt(position, position + m_Front, glm::vec3(0,1,0)); };
        inline glm::mat4 getProjection() const { return m_Projection; };
    
    private:
        glm::vec3 m_Front;
        glm::vec3 m_FrontMovement;
        glm::mat4 m_Projection;
        float m_pitch;
        float m_yaw;
        float m_sensitivity;
};