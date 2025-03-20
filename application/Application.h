#pragma once

#include <cstdint>
//#include <GLFW/glfw3.h>  头文件重复包含
//封装Application(表示了当前应用程序本身)
#define yyh Application::getInstance()

class GLFWwindow;

using ResizeCallBack = void(*)(int width, int height);
using KeyBoardCallBack = void(*)(int key, int action, int mods);

class Application {
public:
    ~Application();
    //用于访问实例的静态函数
    static Application* getInstance();

    bool init(const int& width = 800, const int& height = 600);

    bool update();

    void destroy();

    uint32_t getWidth() const { return mWidth; }
    uint32_t getHeight() const { return mHeight; }

    void setResizeCallBack(ResizeCallBack callBack){mResizeCallBack = callBack;}
    void setKeyBoardCallBack(KeyBoardCallBack callBack){mKeyBoardCallBack = callBack;}

private:
    static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    //全局唯一的静态变量实例
    static Application* mInstance;

    uint32_t mWidth{0};
    uint32_t mHeight{0};
    GLFWwindow* mWindow{nullptr};

    ResizeCallBack mResizeCallBack{nullptr};
    KeyBoardCallBack mKeyBoardCallBack{nullptr};

    //构造函数
    Application();
};

