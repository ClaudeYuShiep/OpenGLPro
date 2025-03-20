#include <iostream>
#include <glFramework/core.h>
#include <glFramework/shader.h>
#include <string>
#include <wrapper/checkError.h>
#include <application/Application.h>

GLuint vao;

Shader* shader = nullptr;

void OnResize(int width, int height)
{
    GL_CALL(glViewport(0, 0, width, height));
    std::cout << "resize" << std::endl;
}

void OnKey(int key, int action, int mods)
{
    std::cout << "key size" << std::endl;
}

// void prepareVBO()
// {
//     //创建一个VBO 没有真正分配显存
//     GLuint vbo = 0;
//     GL_CALL(glGenBuffers(1, &vbo));
//
//     //销毁一个VBO
//     GL_CALL(glDeleteBuffers(1, &vbo));
//     //创建n个VBO
//     GLuint vboArr[] = {0,0,0};
//     GL_CALL(glGenBuffers(3, vboArr));
//     //销毁一个VBO
//     GL_CALL(glDeleteBuffers(3, vboArr));
// }

// void prepare()
// {
//     float vertices[] = {
//         -0.5f, -0.5f, 0.0f,
//          0.5f, -0.5f, 0.0f,
//          0.0f,  0.5f, 0.0f,
//     };
//     //生成一个VBO
//     GLuint vbo = 0;
//     glGenBuffers(1,&vbo);
//     //绑定当前VBO，到opengl状态机的当前vbo插槽上
//     //GL_ARRAY_BUFFER:表示当前vbo插槽
//     glBindBuffer(GL_ARRAY_BUFFER, vbo);
//     //向当前vbo传输数据，开辟显存
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// }

void prepareSingleBuffer()
{
    //准备顶点位置数据和颜色数据

    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    float colors[] = {
         1.0f, 0.0f, 0.0f,
         0.0f, 1.0f, 0.0f,
         0.0f, 0.0f, 1.0f,
    };
    //为位置&颜色数据各生成一个vbo
    GLuint posVbo = 0, colorVbo = 0;
    glGenBuffers(1, &posVbo);
    glGenBuffers(1, &colorVbo);
    //给两个分开的vbo填充数据
    //GL_ARRAY_BUFFER为顶点类型的buffer
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));

    //生成VAO并且绑定
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    //分别将位置/颜色属性的描述信息加入vao中

    //描述位置属性
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);  //绑定该posVbo，vao里的属性才会与其相关
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);

    //描述颜色属性
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    glBindVertexArray(0);

}

void prepareInterLeavedBuffer()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

    vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);//绑定该vbo，vao里的属性才会与其相关

    //位置信息
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)0);
    //颜色信息
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),(void*)(3*sizeof(float)));
}

void prepareVAOForGLTriangles()
{
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    //posVbo
    GLuint posVbo = 0;
    glGenBuffers(1, &posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));

    //vao

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);
    glBindVertexArray(0);
}

void prepareShader()
{
    shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareVAO()
{
    float positions[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    float colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
    };

    //ebo数据 表述哪些点相连
    unsigned int indices[] = {
        0, 1, 2,
        //2, 1, 3
    };

    GLuint posVbo, colorVbo;
    glGenBuffers(1,&posVbo);
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenBuffers(1,&colorVbo);
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1,&ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);

    //绑定vbo ebo
    glBindBuffer(GL_ARRAY_BUFFER, posVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);

    //加入颜色数据
    glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),(void*)0);

    //加入ebo到vao
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBindVertexArray(0);

}

void render()
{
    //清理画布
    GL_CALL(GL_CALL(glClear(GL_COLOR_BUFFER_BIT)));
    //渲染操作
    //绑定当前的program

    shader->begin();

    //绑定当前的vao

    GL_CALL(glBindVertexArray(vao));

    //发出绘制指令

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    shader->end();
}

int main()
{  
    yyh->setResizeCallBack(OnResize);
    yyh->setKeyBoardCallBack(OnKey);
    if (!yyh->init(800,600))
    {
        return -1;
    }
    prepareShader();
    prepareVAO();
    //设置opengl视口以及清理颜色
    GL_CALL(glViewport(0,0,800,600));
    GL_CALL(glClearColor(0.2f, 0.3f, 0.3f, 1.0f));


    //3 执行窗体循环
    while (yyh->update())
    {
        render();

    }
    //4 退出程序前做相关清理
    yyh->destroy();

    return 0;
}
