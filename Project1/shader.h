#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader
{
public:
    GLuint Program;
    Shader(const char* vertexPath, const char* fragmentPath);
    void Use();
    void setVec4(const std::string& name, float x, float y, float z, float w);
};

#endif