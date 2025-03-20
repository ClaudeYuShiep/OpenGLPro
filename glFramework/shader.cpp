#include "shader.h"
#include "../wrapper/checkError.h"
#include "string"
#include "fstream"
#include "sstream"
#include "iostream"


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    //声明装入shader代码字符串
    std::string vertexCode;
    std::string fragmentCode;
    //声明用于读取vs和fs文件的inFileStream
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    //保证ifStream遇到问题能抛出异常
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        //打开文件
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        //将文件输入流中的字符串输入到stringStream里面
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //关闭文件
        vShaderFile.close();
        fShaderFile.close();

        //将字符串从stringStream中读取出来 重定向到codeString中
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESS" << e.what() << std::endl;
    }


    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    //1 创建Shader程序（vs,fs）
    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //2 为shader程序输入shader代码
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);
    //3 执行Shader代码编译
    glCompileShader(vertex);
    //查看是否正确编译
    checkShaderErrors(vertex, "COMPILE");

    glCompileShader(fragment);
    //3 检查vertex编译结果
    //检查vertex编译结果
    checkShaderErrors(fragment, "COMPILE");

    //4 创建一个programme壳子

    mProgram = glCreateProgram();

    //将vs与fs编译好的结果放到program里

    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);
    //执行programme的链接操作，形成最终可执行的shader程序

    glLinkProgram(mProgram);
    //检查链接错误
    checkShaderErrors(mProgram, "LINK");

    //清理
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{

}

void Shader::begin()
{
    GL_CALL(glUseProgram(mProgram));
}

void Shader::end()
{
    GL_CALL(glUseProgram(0));
}

void Shader::setFloat(const std::string& name, float value)
{
    //通过名称拿到Uniform变量的位置Location
    GLint location = GL_CALL(glGetUniformLocation(mProgram,name.c_str()));
    //通过Location更新Uniform变量的值
    GL_CALL(glUniform1f(location, value));
}


void Shader::checkShaderErrors(GLuint target, std::string type)
{
    int success = 0;
    char infoLog[1024];
    if (type == "COMPILE")
    {
        //3 检查vertex编译结果
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        //检查vertex编译结果
        if (!success)
        {
            glGetShaderInfoLog(target, 1024, NULL, infoLog);
            std::cout << "Error: SHADER COMPILE ERROR" << "\n" << infoLog << std::endl;
        }
    }else if (type == "LINK")
    {
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(target, 1024, NULL, infoLog);
            std::cout << "Error: SHADER LINK ERROR" << "\n" << infoLog << std::endl;
        }

    }else
        std::cout << "ERROR::Check shader errors Type" << std::endl;
}
