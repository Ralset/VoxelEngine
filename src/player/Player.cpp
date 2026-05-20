#include "player/Player.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

#include <iostream>

Player::Player(glm::vec3 startLocation,const float speed, const float width, const float height) 
: m_Position(startLocation), m_speed(speed)
{
    m_input = std::make_unique<Input>(width, height);;
    m_camera = std::make_unique<Camera>(0.1f, 45.0f, width, height, 0.1f, 100.0f);
}

void Player::Update() {
    m_input->update();
    m_camera->changeRotation(m_input->getYawChange(), m_input->getPitchChange());

    if(m_input->isKeyHeld(GLFW_KEY_W)) m_Position += m_speed * m_camera->getFront();
    if(m_input->isKeyHeld(GLFW_KEY_S)) m_Position -= m_speed * m_camera->getFront();
    if(m_input->isKeyHeld(GLFW_KEY_A)) m_Position -= m_speed * glm::normalize(glm::cross(m_camera->getFront(), glm::vec3(0.0f, 1.0f, 0.0f)));
    if(m_input->isKeyHeld(GLFW_KEY_D)) m_Position += m_speed * glm::normalize(glm::cross(m_camera->getFront(), glm::vec3(0.0f, 1.0f, 0.0f)));
    if(m_input->isKeyHeld(GLFW_KEY_SPACE)) m_Position += m_speed * glm::vec3(0.0f, 1.0f, 0.0f);
    if(m_input->isKeyHeld(GLFW_KEY_LEFT_SHIFT)) m_Position -= m_speed * glm::vec3(0.0f, 1.0f, 0.0f);

    std::cout<<m_Position.x<<' '<<m_Position.y<<' '<<m_Position.z<<'\n';
}