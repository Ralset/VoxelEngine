#include "core/Input.h"

#include <GLFW/glfw3.h>
#include <cstring>
#include <iostream>

Input::Input(const float width, const float height) 
: m_x(width/2), m_y(height/2), m_previousX(width/2), m_previousY(height/2), m_firstMove(true), m_LMB(false), m_RMB(false), m_previousLMB(false), m_previousRMB(false)
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

    m_previousLMB = m_LMB;
    m_previousRMB = m_RMB;
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

void Input::onMouseButtonClick(int button, int action)
{
    if(action == GLFW_PRESS){
        if(button == GLFW_MOUSE_BUTTON_LEFT) m_LMB = true;
        else if(button == GLFW_MOUSE_BUTTON_RIGHT) m_RMB = true;
    }
    else if(action == GLFW_RELEASE){
        if(button == GLFW_MOUSE_BUTTON_LEFT) m_LMB = false;
        else if(button == GLFW_MOUSE_BUTTON_RIGHT) m_RMB = false;
    }
}