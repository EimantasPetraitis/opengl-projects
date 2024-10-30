#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Texture.h"
#include "BatchRenderer.h"

#include "tests/TestMenu.h"
#include "tests/TestClearColor.h"
#include "tests/TestPolygon.h"
#include "tests/TestTexture.h"
#include "tests/TestBatchRendering.h"
#include "tests/TestBatchRenderingGrid.h"
#include "tests/TestBatchRendererGrid.h"
#include "tests/TestBasic3D.h"
#include "tests/TestCube.h"
#include "tests/TestCamera.h"
#include "tests/TestLighting.h"
#include "tests/TestLightingMaps.h"

int main()
{

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    int width = 1280;
    int height = 960;
    
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        std::cout << "GLEW init error occured." << "\n";
    
    std::cout << "\n\nOpenGL version " << glGetString(GL_VERSION) << "\n\n\n";

    const char* glslVersion = "#version 460";

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);

    Renderer::EnableDebuging();

    tests::Test* currentTest;
    tests::TestMenu* testMenu = new tests::TestMenu(currentTest, window);
    currentTest = testMenu;

    testMenu->AddTest<tests::TestClearColor>("Clear Color");
    testMenu->AddTest<tests::TestPolygon>("Polygon");
    testMenu->AddTest<tests::TestTexture>("Texture");
    testMenu->AddTest<tests::TestBatchRendering>("Batch Rendering");
    testMenu->AddTest<tests::TestBatchRenderingGrid>("Batch Rendering - Grid");
    testMenu->AddTest<tests::TestBatchRendererGrid>("Batch Renderer Class - Grid");
    testMenu->AddTest<tests::TestBasic3D>("Basic 3D");
    testMenu->AddTest<tests::TestCube>("3D - Cube");
    testMenu->AddTest<tests::TestCamera>("3D - Camera");
    testMenu->AddTest<tests::TestLighting>("3D - Lighting");
    testMenu->AddTest<tests::TestLightingMaps>("3D - Lighting Maps and Lights");

    while (!glfwWindowShouldClose(window))
    {

        if (currentTest)
            currentTest->ProcessInput(window);
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::Clear();

        if (currentTest)
        {

            currentTest->OnUpdate(io.DeltaTime);
            currentTest->OnRender();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Properties");
            if (currentTest != testMenu && ImGui::Button("Back"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* currentContextBackup = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(currentContextBackup);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    if (currentTest != testMenu)
        delete testMenu;
    delete currentTest;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    
}