cmake_minimum_required(VERSION 3.27)
project(imgui_docking VERSION 1.90.0 LANGUAGES C CXX)

set(
    CPP_SOURCE_FILES
    imgui.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
)

set(
    CPP_HEADER_FILES
    imgui.h
    imconfig.h
    imgui_internal.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui_impl_glfw.h
    imgui_impl_opengl3.h
    imgui_impl_opengl3_loader.h
)

add_library(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})

target_link_libraries(
    ${PROJECT_NAME}
    glfw
)