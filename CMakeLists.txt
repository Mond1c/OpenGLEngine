cmake_minimum_required(VERSION 3.17)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)
add_subdirectory(glew)

include_directories(Core)

add_executable(Engine Core/Debug.h Engine.h Engine.cpp Parser/File.h Parser/File.cpp Core/GameObject.h Core/GameObject.cpp
        Parser/GameObjectParser.h Parser/GameObjectParser.cpp Physics/ICollider.h Physics/ICollider.cpp Core/IComponent.h main.cpp Core/MonoBehaviour.h Physics/Physics.cpp Physics/Physics.h
        Core/Settings.h Core/Transform.h Core/Utility.h Core/Window.h Core/Window.cpp)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew/include)

target_link_libraries(Engine glfw libglew_static)