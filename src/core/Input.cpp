#include "Input.h"
#include <cstring>
#include <GLFW/glfw3.h>

#include <iostream>

Input::Input()
{
    mousePosition = {0,0};
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
    mousePosition = {xpos, ypos};
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