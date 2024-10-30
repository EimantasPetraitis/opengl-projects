#include "TestBatchRenderingGrid.h"

#include <array>

#include <GL/glew.h>
#include <imgui.h>

static unsigned int CreateQuadInArray(
    Vertex* targetArray, unsigned int index,
    Vector2 position, Vector2 scale, Vector4 color,
    int textureIndex = -1
)
{
    
    targetArray[index].position = {
        position.x - 0.5f * scale.x,
        position.y - 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 0.0f, 0.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    targetArray[index].position = {
        position.x + 0.5f * scale.x,
        position.y - 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 1.0f, 0.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    targetArray[index].position = {
        position.x + 0.5f * scale.x,
        position.y + 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 1.0f, 1.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    targetArray[index].position = {
        position.x - 0.5f * scale.x,
        position.y + 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 0.0f, 1.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    return index;

}

namespace tests
{

    TestBatchRenderingGrid::TestBatchRenderingGrid()
        : windowWidth(1280),
        windowHeight(960),
        maxQuadCount(64),
        maxVertexCount(maxQuadCount * 4),
        maxIndexCount(maxQuadCount * 6),
        vertexBuffer(), indexBuffer(),
        program
        (
            "resources/shaders/batch.vert",
            "resources/shaders/batch.frag"
        ),
        cornerPosition { -400.0f, -400.0f },
        squareScale { 100.0f, 100.0f },
        colorWhite { 1.0f, 1.0f, 1.0f, 1.0f },
        colorBlack { 0.0f, 0.0f, 0.0f, 1.0f },
        textureA("resources/textures/UV test.png"),
        textureB("resources/textures/Wind-waves.png"),
        textureIndexWhite(-1), textureIndexBlack(-1),
        textureASlot(0), textureBSlot(1)
    {

        vertexBuffer.Generate(maxVertexCount * sizeof(Vertex), true);

        unsigned int indices[maxIndexCount];

        int offset = 0;
        
        for (int i = 0; i < maxIndexCount; i += 6)
        {

            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;

        }
        
        indexBuffer.Generate(
            indices, sizeof(indices), maxIndexCount
        );
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        layout.Push(GL_FLOAT, 2, false);  // Position
        layout.Push(GL_FLOAT, 4, false);  // Color
        layout.Push(GL_FLOAT, 2, false);  // Texture coordinates
        layout.Push(GL_FLOAT, 1, false);  // Texture index

        vertexArray.AddBuffer(vertexBuffer, layout);

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
        textureA.Bind(textureASlot);
        textureB.Bind(textureBSlot);

    }

    TestBatchRenderingGrid::~TestBatchRenderingGrid()
    {}

    void TestBatchRenderingGrid::OnUpdate(float deltaTime)
    {}

    void TestBatchRenderingGrid::OnRender()
    {

        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int indexCount = 0;

        Vertex vertices[maxVertexCount];
        unsigned int index = 0;

        for (int x = 0; x < 8; x++)
        {
            for (int y = 0; y < 8; y++)
            {

                Vector4 color;
                int textureIndex;

                bool isWhite = (x + y) % 2 == 1;
                
                if (isWhite)
                {
                    color = colorWhite;
                    textureIndex = textureIndexWhite;
                }
                else
                {
                    color = colorBlack;
                    textureIndex = textureIndexBlack;
                }

                index = CreateQuadInArray(
                    vertices, index,
                    Vector2 {
                        cornerPosition.x + (float)x * squareScale.x,
                        cornerPosition.y + (float)y * squareScale.y,
                    },
                    squareScale, color, textureIndex
                );
                indexCount += 6;

            }
        }
        
        vertexBuffer.Bind();
        vertexBuffer.SetData(0, sizeof(vertices), vertices);
        
        indexBuffer.Bind();
        vertexArray.Bind();

        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;

        program.Bind();
        program.SetUniformMatrix4Floats("u_MVPMatrix", mvpMatrix);

        int textureSamplers[2] = { 0, 1 };
        program.SetUniform1IntArray(
            "u_Textures", 2, textureSamplers
        );

        Renderer::Draw(
            vertexArray, indexBuffer, program, indexCount
        );

    }

    void TestBatchRenderingGrid::OnImGuiRender()
    {

        ImGui::SliderFloat2(
            "Position", &cornerPosition.x,
            -(float)windowWidth, (float)windowWidth
        );
        ImGui::SliderFloat2(
            "Square scale", &squareScale.x,
            -(float)windowWidth/8, (float)windowWidth/8
        );
        
        ImGui::SeparatorText("White squares");
        ImGui::ColorEdit4("White square color", &colorWhite.x);
        ImGui::InputInt("White square texture", &textureIndexWhite);

        ImGui::SeparatorText("Black squares");
        ImGui::ColorEdit4("Black square color", &colorBlack.x);
        ImGui::InputInt("Black square texture", &textureIndexBlack);

    }

}