#include "core/Window.h"
#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
    if (!glfwInit())
        return -1;

    Window ekran(800, 600, "Test");

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    while (!ekran.shouldWindowClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        ekran.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}