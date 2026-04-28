#include "core/Window.h"
#include <iostream>

int main()
{
    Window ekran(800, 600, "Test");

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(ekran.get_window()))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(ekran.get_window());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}