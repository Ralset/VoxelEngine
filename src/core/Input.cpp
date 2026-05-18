#include "Input.h"
#include <cstring>
#include <GLFW/glfw3.h>

#include <iostream>

Input::Input() : m_x(640), m_y(360), m_pitch(0), m_yaw(270)
{
    firstMouse = true;
    memset(m_currentKeys, false, 350 * sizeof(bool));
    memset(m_previousKeys, false, 350 * sizeof(bool));
}

void Input::update()
{
    memcpy(m_previousKeys, m_currentKeys, 350*sizeof(bool));
}

void Input::onKey(int key, int action)
{
    if(action == GLFW_PRESS)m_currentKeys[key]=true;
    else if(action == GLFW_RELEASE)m_currentKeys[key]=false;
    return;
}

void Input::onCursorMove(double xpos, double ypos)
{
    if (firstMouse)
    {
        m_x = xpos;
        m_y = ypos;
        firstMouse = false;
    }

    float xoffest = xpos - m_x;
    float yoffset = m_y - ypos;
    m_x = xpos;
    m_y = ypos;
    m_yaw += xoffest * m_mouseSensitivity;
    m_pitch += yoffset * m_mouseSensitivity;
    m_pitch = std::max(std::min(m_pitch, 89.0f), -89.0f);
    if(m_yaw <= 0) m_yaw += 360;
    if(m_yaw >= 360) m_yaw -= 360;
}

bool Input::isKeyHeld(int key) const{
    return m_currentKeys[key] & m_previousKeys[key];
}

bool Input::isKeyPressed(int key) const{
    return m_currentKeys[key] & (!m_previousKeys[key]);
}

bool Input::isKeyReleased(int key) const{
    return (!m_currentKeys[key]) & m_previousKeys[key];
}