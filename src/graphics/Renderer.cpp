#include "Renderer.h"

#include <string>
#include <stdexcept>

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        throw std::runtime_error("OpenGL Error (" + std::to_string(error) + ") in " + function + " at " + file + ":" + std::to_string(line));
    }
}
