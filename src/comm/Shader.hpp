#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    unsigned int ID;

    Shader(const GLchar *vetexPath, const GLchar *fragmentPath);
    void use();
    void setBool(const std::string &name, bool vlaue) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void set4f(const std::string &name, float f1, float f2, float f3, float f4) const;
    void setMat4(const std::string &name, const glm::mat4 &mat);
};

#endif /* SHADER_H */
