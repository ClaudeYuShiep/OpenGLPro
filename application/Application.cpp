#include "Application.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
//初始化Application的静态变量
Application* Application::mInstance = nullptr;
Application* Application::getInstance()
{
    //如果mInstance已经实例化了（new出来了） 就直接返回
    //否则需要先new出来 再返回
    if (mInstance == nullptr)
        mInstance = new Application();
    return mInstance;
}

bool Application::init(const int& width, const int& height)
{
    mWidth = width;
    mHeight = height;
    //1 初始化GLFW基本环境 主版本号和次版本号 启动核心模式（非立即渲染模式）
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //2 创建窗体对象 设置当前窗体对象为OpenGl的绘制舞台
    mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL Project", nullptr, nullptr);
    if (mWindow == nullptr)
        return false;
    glfwMakeContextCurrent(mWindow);
    //使用glad加载所有当前版本opengl的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD" << std::endl;
        return false;
    }

    //窗口大小响应
    glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCallback);

    //this为当前全局唯一的Application对象
    glfwSetWindowUserPointer(mWindow, this);

    //键盘响应
    glfwSetKeyCallback(mWindow, keyCallBack);


    return true;
}

bool Application::update()
{
    if (glfwWindowShouldClose(mWindow))
        return false;

        //接收并分发窗体消息
        //检查消息队列是否需要处理的鼠标、键盘等消息
        //如果有的话就将消息批量处理、清空队列
        glfwPollEvents();
        //切换双缓存
        glfwSwapBuffers(mWindow);

    return true;
}

void Application::destroy()
{
    //4 退出程序前做相关清理
    glfwTerminate();
}

Application::Application()
{

}

Application::~Application()
{

}

void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << "Framebuffer size" << std::endl;

    Application* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mResizeCallBack != nullptr)
        self->mResizeCallBack(width, height);
    // if (Application::getInstance()->mResizeCallBack != nullptr)
    //     Application::getInstance()->mResizeCallBack(width, height);
}

void Application::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* self = (Application*)glfwGetWindowUserPointer(window);
    if (self->mKeyBoardCallBack != nullptr)
        self->mKeyBoardCallBack(key, action, mods);
}