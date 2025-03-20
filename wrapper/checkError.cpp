#include "checkError.h"
#include <iostream>
#include <glad/glad.h>
#include <string>
#include <assert.h>

void checkError()
{
    GLenum errorCode = glGetError();
    std::string error = "";
    if (errorCode != GL_NO_ERROR)
    {
        switch (errorCode)
        {
        case GL_INVALID_ENUM: error = "INVALID_ENUM" ;break;
        case GL_INVALID_VALUE: error = "INVALID_VALUE";break;
        default:
            break;
        }
        std::cout << error << std::endl;
        //根据传入的bool值决定程序是否停止
        assert(false);
    }
}