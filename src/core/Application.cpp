#include "Application.h"

#include "core/Window.h"
#include "graphics/Renderer.h"
#include "graphics/VertexBuffer.h"
#include "graphics/IndexBuffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

//For now------------------------------------------------------
static std::string ParseShader(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open()){
        throw std::runtime_error("ERROR: Couldn't open " + filepath);
    } 
    std::stringstream buffer;
    buffer<<file.rdbuf();
    return buffer.str();
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (!result){
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout<<"Failed to compile "<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<" shader!"<<std::endl;
        std::cout<<message<<std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    GLCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDetachShader(program, vs));
    GLCall(glDetachShader(program, fs));
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}
//-----------------------------------

Application::Application() {
    ASSERT(glfwInit());
    m_window = std::make_unique<Window>(800, 600, "VoxelGame");
    glfwSetWindowUserPointer(m_window->getWindow(), this);
    glfwSetFramebufferSizeCallback(m_window->getWindow(), resizeCallBack);
    glfwSetKeyCallback(m_window->getWindow(), keyCallBack);
    glfwSetCursorPosCallback(m_window->getWindow(), cursorPosCallback);
}

Application::~Application() {
    glfwTerminate();
}

void Application::resizeCallBack(GLFWwindow* window, int width, int height){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->m_window->resizeWindow(width, height);
}

void Application::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->m_input.onKey(key, action);
}

void Application::cursorPosCallback(GLFWwindow* window, double xpos, double ypos){
    Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    app->m_input.onCursorMove(xpos, ypos);
}

void Application::Run()
{
    float points[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexBuffer vbo(points, 8 * sizeof(float));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));

    IndexBuffer ebo(indices, 6 * sizeof(unsigned int));

    std::string vertexShader=ParseShader("assets/shaders/Vertex.shader");
    std::string fragmentShader=ParseShader("assets/shaders/Fragment.shader");
    
    GLCall(unsigned int shader = CreateShader(vertexShader, fragmentShader));
    GLCall(glUseProgram(shader));

    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location, 0.2f, 0.3f, 0.8f, 1.0f));

    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    vbo.Unbind();
    ebo.Unbind();

    float r = 0.0f;
    float increment = 0.05f;

    while (!m_window->shouldWindowClose()&&!m_input.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        m_input.update();
        //std::cout<<m_input.mousePosition.x<<' '<<m_input.mousePosition.y<<std::endl;
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        r += increment;

        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

        GLCall(glBindVertexArray(vao));
        ebo.Bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        if (r > 1.0f || r < 0.0f)
            increment *= -1;

        m_window->swapBuffers();
        glfwPollEvents();
    }

    GLCall(glDeleteProgram(shader));
}