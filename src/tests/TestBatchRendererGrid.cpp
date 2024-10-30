#include "TestBatchRendererGrid.h"

#include <array>

#include <GL/glew.h>
#include <imgui.h>

namespace tests
{

    TestBatchRendererGrid::TestBatchRendererGrid()
        : windowWidth(1280),
        windowHeight(960),
        program
        (
            "resources/shaders/default.vert",
            "resources/shaders/default.frag"
        ),
        cornerPosition { -400.0f, -400.0f },
        squareScale { 25.0f, 25.0f },
        textureA("resources/textures/UV test.png"),
        textureB("resources/textures/Wind-waves.png")
    {

        BatchRenderer::Init();
        BatchRenderer::SetShader(program);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        projectionMatrix = glm::ortho(
            -(float)windowWidth/2, (float)windowWidth/2,
            -(float)windowHeight/2, (float)windowHeight/2,
            -1.0f, 1.0f
        );
        viewMatrix = glm::inverse(
            glm::translate(
                glm::mat4(1.0f),
                glm::vec3(0, 0, 0)
            )
        );

        program.Bind();

    }

    TestBatchRendererGrid::~TestBatchRendererGrid()
    {

        BatchRenderer::Shutdown();

    }

    void TestBatchRendererGrid::OnUpdate(float deltaTime)
    {}

    void TestBatchRendererGrid::OnRender()
    {

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        BatchRenderer::BeginBatch();

        for (int x = 0; x < 30; x++)
        {
            for (int y = 0; y < 30; y++)
            {

                bool isWhite = (x + y) % 2 == 1;
                
                if (isWhite)
                {
                    
                    BatchRenderer::DrawQuad(
                        Vector2 {
                            cornerPosition.x + (float)x * squareScale.x,
                            cornerPosition.y + (float)y * squareScale.y,
                        },
                        squareScale, textureA
                    );

                }
                else
                {

                    BatchRenderer::DrawQuad(
                        Vector2 {
                            cornerPosition.x + (float)x * squareScale.x,
                            cornerPosition.y + (float)y * squareScale.y,
                        },
                        squareScale, textureB
                    );

                }

            }
        }
        
        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;
        program.Bind();
        program.SetUniformMatrix4Floats("u_MVPMatrix", mvpMatrix);

        BatchRenderer::EndBatch();
        BatchRenderer::SendBatch();

    }

    void TestBatchRendererGrid::OnImGuiRender()
    {

        ImGui::SliderFloat2(
            "Position", &cornerPosition.x,
            -(float)windowWidth, (float)windowWidth
        );
        ImGui::SliderFloat2(
            "Square scale", &squareScale.x,
            -(float)windowWidth/8, (float)windowWidth/8
        );

    }

}