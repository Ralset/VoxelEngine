# pragma once

#include "glm/glm.hpp"

class Shader{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
        void use() const;
        void setUniform(const std::string &name, int data);    
        void setUniform(const std::string &name, bool data);
        void setUniform(const std::string &name, float data);    
        void setUniform(const std::string &name, glm::vec2 data);
        void setUniform(const std::string &name, glm::vec3 data);
        void setUniform(const std::string &name, glm::vec4 data);
        void setUniform(const std::string &name, glm::mat3 data);
        void setUniform(const std::string &name, glm::mat4 data);

    private:
        unsigned int u_programID;
        std::string parseShader(const std::string& path);
        unsigned int compileShader(unsigned int type, const std::string& source);
};