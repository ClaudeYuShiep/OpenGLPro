cmake_minimum_required(VERSION 3.30)

project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

#往项目中加入预编译宏
add_definitions(-DDEBUG)

#把ASSETS指代的目录集合的内容，都拷贝到可执行文件目录下
file(GLOB ASSETS "./assets")

#把ASSETS指代的目录集合的内容，都拷贝到可执行文件目录下
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/third_party/include)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR})

link_directories(
        SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lib
)

add_subdirectory(wrapper)
add_subdirectory(application)
add_subdirectory(glFramework)

#本工程所有cpp文件编译连接，生成exe
add_executable(OpenGL main.cpp glad.c)

target_link_libraries(OpenGL wrapper #自定义库
        app #自定义库
        fw #自定义库
        libglfw3.a
)