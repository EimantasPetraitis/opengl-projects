cmake_minimum_required(VERSION 3.27)
project(OpenGLRenderer VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

include_directories(dependencies/stb_image)

set(
    CPP_SOURCE_FILES
    src/Main.cpp
    src/VertexBuffer.cpp
    src/VertexBufferLayout.cpp
    src/IndexBuffer.cpp
    src/VertexArray.cpp
    src/ShaderProgram.cpp
    src/Renderer.cpp
    src/BatchRenderer.cpp
    src/Texture.cpp
    src/Vector.cpp
    src/Mesh.cpp
    src/Cube.cpp
    src/Camera.cpp
    src/tests/TestMenu.cpp
    src/tests/TestClearColor.cpp
    src/tests/TestPolygon.cpp
    src/tests/TestTexture.cpp
    src/tests/TestBatchRendering.cpp
    src/tests/TestBatchRenderingGrid.cpp
    src/tests/TestBatchRendererGrid.cpp
    src/tests/TestBasic3D.cpp
    src/tests/TestCube.cpp
    src/tests/TestCamera.cpp
    src/tests/TestLighting.cpp
    src/tests/TestLightingMaps.cpp
    dependencies/stb_image/stb_image.cpp
)

set(
    CPP_HEADER_FILES
    src/VertexBuffer.h
    src/VertexBufferLayout.h
    src/IndexBuffer.h
    src/VertexArray.h
    src/ShaderProgram.h
    src/Renderer.h
    src/BatchRenderer.h
    src/Texture.h
    src/Vector.h
    src/Vertex.h
    src/Vertex3D.h
    src/MeshVertex.h
    src/PosNormalVertex.h
    src/Mesh.h
    src/Cube.h
    src/Camera.h
    src/MaterialPlain.h
    src/Material.h
    src/PointLight.h
    src/DirectionalLight.h
    src/tests/Test.h
    src/tests/TestMenu.h
    src/tests/TestClearColor.h
    src/tests/TestPolygon.h
    src/tests/TestTexture.h
    src/tests/TestBatchRendering.h
    src/tests/TestBatchRenderingGrid.h
    src/tests/TestBatchRendererGrid.h
    src/tests/TestBasic3D.h
    src/tests/TestCube.h
    src/tests/TestCamera.h
    src/tests/TestLighting.h
    src/tests/TestLightingMaps.h
    dependencies/stb_image/stb_image.h
)

add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES} ${CPP_HEADER_FILES})

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glew)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/imgui_docking)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC dependencies/glfw/include
    PUBLIC dependencies/glew/include
    PUBLIC dependencies/glm
    PUBLIC dependencies/imgui_docking
)

target_link_libraries(
    ${PROJECT_NAME}
    opengl32 glfw libglew_static glm imgui_docking
)

add_compile_definitions(GLEW_STATIC)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)