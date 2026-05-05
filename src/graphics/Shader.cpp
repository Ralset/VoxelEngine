#include "Shader.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    GLCall(u_programID = glCreateProgram());
    std::string vertexShader = parseShader(vertexPath);
    std::string fragmentShader = parseShader(fragmentPath);

    GLCall(unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader));
    GLCall(unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader));

    GLCall(glAttachShader(u_programID, vs));
    GLCall(glAttachShader(u_programID, fs));
    GLCall(glLinkProgram(u_programID));
    GLCall(glValidateProgram(u_programID));

    GLCall(glDetachShader(u_programID, vs));
    GLCall(glDetachShader(u_programID, fs));
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
}

Shader::~Shader(){
    GLCall(glDeleteProgram(u_programID));
}

void Shader::use() const{
    GLCall(glUseProgram(u_programID));
}

void Shader::setUniform(const std::string &name, int data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniform1i(loc, data));
}

void Shader::setUniform(const std::string &name, bool data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniform1i(loc, (int)data));
}

void Shader::setUniform(const std::string &name, float data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniform1f(loc, data));
}

void Shader::setUniform(const std::string &name, glm::vec2 data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniform2f(loc, data.x,data.y));

}

void Shader::setUniform(const std::string &name, glm::vec3 data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniform3f(loc, data.x,data.y,data.z));
}

void Shader::setUniform(const std::string &name, glm::vec4 data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniform4f(loc, data.x,data.y,data.z,data.w));
}

void Shader::setUniform(const std::string &name, glm::mat3 data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(data)));
}

void Shader::setUniform(const std::string &name, glm::mat4 data) {
    GLCall(int loc = glGetUniformLocation(u_programID, name.c_str()));
    ASSERT(loc != -1);
    GLCall(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data)));
}

std::string Shader::parseShader(const std::string& path){
    std::ifstream file(path);
    if (!file.is_open()){
        throw std::runtime_error("ERROR: Couldn't open " + path);
    } 
    std::stringstream buffer;
    buffer<<file.rdbuf();
    return buffer.str();

}
unsigned int Shader::compileShader(unsigned int type, const std::string& source){
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
