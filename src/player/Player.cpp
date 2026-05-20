#include "player/Player.h"

#include "world/World.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLFW/glfw3.h"

#include <iostream>

Player::Player(World* world, glm::vec3 startLocation, const float playerHeight,const float speed, const float width, const float height) 
: m_Position(startLocation), m_speed(speed), m_playerHeight(playerHeight)
{
    currentWorld = world;
    m_input = std::make_unique<Input>(width, height);;
    m_camera = std::make_unique<Camera>(0.1f, 45.0f, width, height, 0.1f, 100.0f);
}

void Player::Update() {
    inputUpdate();
    m_input->update();
    m_camera->changeRotation(m_input->getYawChange(), m_input->getPitchChange());

    //std::cout<<"Camera dir - "<<m_camera->getDirection().x<<' '<<m_camera->getDirection().y<<' '<<m_camera->getDirection().z<<std::endl;
    //std::cout<<m_Position.x<<' '<<m_Position.y<<' '<<m_Position.z<<'\n';
}

void Player::inputUpdate(){
    if(m_input->isKeyHeld(GLFW_KEY_W)) m_Position += m_speed * m_camera->getMovDireciton();
    if(m_input->isKeyHeld(GLFW_KEY_S)) m_Position -= m_speed * m_camera->getMovDireciton();
    if(m_input->isKeyHeld(GLFW_KEY_A)) m_Position -= m_speed * glm::normalize(glm::cross(m_camera->getMovDireciton(), glm::vec3(0.0f, 1.0f, 0.0f)));
    if(m_input->isKeyHeld(GLFW_KEY_D)) m_Position += m_speed * glm::normalize(glm::cross(m_camera->getMovDireciton(), glm::vec3(0.0f, 1.0f, 0.0f)));
    if(m_input->isKeyHeld(GLFW_KEY_SPACE)) m_Position += m_speed * glm::vec3(0.0f, 1.0f, 0.0f);
    if(m_input->isKeyHeld(GLFW_KEY_LEFT_SHIFT)) m_Position -= m_speed * glm::vec3(0.0f, 1.0f, 0.0f);
    if(m_input->isLMBClicked()) {
        if(currentWorld->canReachBlock(m_Position + glm::vec3(0.0f, m_playerHeight, 0.0f), m_camera->getDirection(), 10.0f)){
            currentWorld->destroyBlock(m_Position + glm::vec3(0.0f, m_playerHeight, 0.0f), m_camera->getDirection(), 10.0f);
        }
    }
    if(m_input->isRMBClicked()) {
        if(currentWorld->canReachBlock(m_Position + glm::vec3(0.0f, m_playerHeight, 0.0f), m_camera->getDirection(), 10.0f)){
            currentWorld->placeBlock(m_Position + glm::vec3(0.0f, m_playerHeight, 0.0f), m_camera->getDirection(), 10.0f);
        }
    }
}