cmake_minimum_required(VERSION 3.17)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL)
find_package(glfw3 REQUIRED)

add_executable(Engine Engine.cpp Parser/File.cpp core/GameObject.cpp
        Parser/GameObjectParser.cpp Physics/ICollider.cpp main.cpp Physics/Physics.cpp
        core/Window.cpp)


target_link_libraries(Engine glfw OpenGL::GL)