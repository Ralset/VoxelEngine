#include "core/Input.h"

#include <GLFW/glfw3.h>
#include <cstring>
#include <iostream>

Input::Input(const float width, const float height) 
: m_x(width/2), m_y(height/2), m_previousX(width/2), m_previousY(height/2), m_firstMove(true)
{
    memset(m_currentKeys, false, 350 * sizeof(bool));
    memset(m_previousKeys, false, 350 * sizeof(bool));
}

void Input::update()
{
    memcpy(m_previousKeys, m_currentKeys, 350*sizeof(bool));
    m_yawChange   = m_x - m_previousX;
    m_pitchChange = m_previousY - m_y;

    m_previousX = m_x;
    m_previousY = m_y;
}

void Input::onKey(int key, int action)
{
    if(action == GLFW_PRESS)m_currentKeys[key]=true;
    else if(action == GLFW_RELEASE)m_currentKeys[key]=false;
    return;
}

void Input::onCursorMove(double xpos, double ypos)
{
    if(m_firstMove)
    {
        m_previousX = xpos;
        m_previousY = ypos;
        m_firstMove = false;
    }
    m_x = xpos;
    m_y = ypos;
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