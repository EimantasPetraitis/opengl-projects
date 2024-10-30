#include "TestClearColor.h"

#include <GL/glew.h>
#include <imgui.h>

namespace tests
{

    TestClearColor::TestClearColor()
        : clearColor { 0.0f, 0.0f, 0.0f, 1.0f }
    {}

    TestClearColor::~TestClearColor()
    {}

    void TestClearColor::OnUpdate(float deltaTime)
    {}

    void TestClearColor::OnRender()
    {

        glClearColor(
            clearColor[0], clearColor[1], clearColor[2], clearColor[3]
        );
        glClear(GL_COLOR_BUFFER_BIT);

    }

    void TestClearColor::OnImGuiRender()
    {

        ImGui::ColorEdit4("Clear Color", clearColor);

    }

}