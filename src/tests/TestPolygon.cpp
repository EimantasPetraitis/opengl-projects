#include "TestPolygon.h"

#include <GL/glew.h>
#include <imgui.h>

namespace tests
{

    TestPolygon::TestPolygon()
        : vertices
        {
            -0.5f,  0.5f,
             0.5f,  0.5f,
             0.5f, -0.5f,
            -0.5f, -0.5f,
        },
        indices
        {
            0, 1, 2,
            0, 2, 3
        },
        color { 1.0f, 1.0f, 1.0f, 1.0f },
        vertexBuffer(4 * 2 * sizeof(float), vertices),
        indexBuffer(indices, 6 * sizeof(unsigned int), 6),
        program
        (
            "resources/shaders/color.vert",
            "resources/shaders/color.frag"
        )
    {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        layout.Push(GL_FLOAT, 2, false);
        vertexArray.Generate();
        vertexArray.AddBuffer(vertexBuffer, layout);

        program.Bind();

    }

    TestPolygon::~TestPolygon()
    {}

    void TestPolygon::OnUpdate(float deltaTime)
    {}

    void TestPolygon::OnRender()
    {

        indexBuffer.Bind();
        vertexArray.Bind();
        program.Bind();

        program.SetUniform4Floats(
            "u_Color", color[0], color[1], color[2], color[3]
        );

        Renderer::Draw(vertexArray, indexBuffer, program);

    }

    void TestPolygon::OnImGuiRender()
    {

        ImGui::ColorEdit4("Color", &color[0]);

    }

}