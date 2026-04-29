#include "core/Window.h"

#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
    if (!glfwInit())
        return -1;

    Window ekran(800, 600, "Test");

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    float points[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), points, GL_STATIC_DRAW);

    while (!ekran.shouldWindowClose())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        ekran.swapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}