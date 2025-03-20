#pragma once

#include "core.h"
#include "string"
class Shader {

public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void begin(); //开始使用当前的shader

    void end(); //结束使用当前的shader

private:
    GLuint mProgram{0};

    //shader program
    void checkShaderErrors(GLuint target, std::string type);
};


