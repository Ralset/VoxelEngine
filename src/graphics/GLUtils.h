#pragma once

#include <glad/glad.h>

#define ASSERT(x) if(!(x)) throw std::runtime_error(std::string("Assert failed: ") + #x + " at line: " + std::to_string(__LINE__) + " at file: " + __FILE__);
#define GLCall(x)\
    GLClearError();\
    x;\
    GLLogCall(#x, __FILE__, __LINE__)

void GLClearError();
void GLLogCall(const char* function, const char* file, int line);
