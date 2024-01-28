cmake_minimum_required(VERSION 3.26)
project(dllmenu)

set(CMAKE_CXX_STANDARD 20)

include_directories(imgui-master)
include_directories(imgui-master/backends)

file(GLOB ims imgui-master/*.cpp)

add_library(dllmenu SHARED main.cpp ${ims}
        imgui-master/backends/imgui_impl_opengl2.cpp
        imgui-master/backends/imgui_impl_win32.cpp
        src/glStaff/glStaff.cpp
        src/glStaff/glStaff.h
        src/guiStaff/guiStaff.cpp
        src/guiStaff/guiStaff.h
        json.h)

target_link_libraries(dllmenu PUBLIC  opengl32)

