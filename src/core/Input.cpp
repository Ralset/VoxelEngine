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
    std::cout<<"NASAO INPUT ZA "<<key<<std::endl;
    return;
}