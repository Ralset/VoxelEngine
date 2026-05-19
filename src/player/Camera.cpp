#include "player/Camera.h"

#include <iostream>

Camera::Camera(const float sensitivity,const float fov, const float width, const float height, const float nearPlane, const float farPlane) 
: m_pitch(0), m_yaw(270), m_sensitivity(sensitivity)
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_Front = glm::normalize(direction);
    m_FrontMovement = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
    m_Projection = glm::perspective(glm::radians(fov), width / height, nearPlane, farPlane);
}

void Camera::changeRotation(const float xoffset, const float yoffset)
{
    m_yaw += xoffset * m_sensitivity;
    m_pitch += yoffset * m_sensitivity;
    m_pitch = std::max(std::min(m_pitch, 89.0f), -89.0f);
    if(m_yaw <= 0) m_yaw += 360;
    if(m_yaw >= 360) m_yaw -= 360;

    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_Front = glm::normalize(direction);
    m_FrontMovement = glm::normalize(glm::vec3(direction.x, 0.0f, direction.z));
}
