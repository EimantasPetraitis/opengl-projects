#include "TestBatchRendering.h"

#include <array>

#include <GL/glew.h>
#include <imgui.h>

#define GLM_SWIZZLE
#define MAX_NUM_VERTICES 64

static std::array<Vertex, 4> CreateQuad(
    Vector2 position, Vector2 scale, Vector4 color,
    int textureIndex = -1
)
{
    
    Vertex v0;
    v0.position = {
        position.x - 0.5f * scale.x,
        position.y - 0.5f * scale.y
    };
    v0.color = color;
    v0.textureCoordinates = { 0.0f, 0.0f };
    v0.textureIndex = (float)textureIndex;

    Vertex v1;
    v1.position = {
        position.x + 0.5f * scale.x,
        position.y - 0.5f * scale.y
    };
    v1.color = color;
    v1.textureCoordinates = { 1.0f, 0.0f };
    v1.textureIndex = (float)textureIndex;

    Vertex v2;
    v2.position = {
        position.x + 0.5f * scale.x,
        position.y + 0.5f * scale.y
    };
    v2.color = color;
    v2.textureCoordinates = { 1.0f, 1.0f };
    v2.textureIndex = (float)textureIndex;

    Vertex v3;
    v3.position = {
        position.x - 0.5f * scale.x,
        position.y + 0.5f * scale.y
    };
    v3.color = color;
    v3.textureCoordinates = { 0.0f, 1.0f };
    v3.textureIndex = (float)textureIndex;

    return { v0, v1, v2, v3 };

}

namespace tests
{

    TestBatchRendering::TestBatchRendering()
        : windowWidth(1280),
        windowHeight(960),
        maxQuadCount(16),
        maxVertexCount(maxQuadCount * 4),
        maxIndexCount(maxQuadCount * 6),
        vertexBuffer(), indexBuffer(),
        program
        (
            "resources/shaders/batch.vert",
            "resources/shaders/batch.frag"
        ),
        positionA { -300.0f, -50.0f },
        scaleA { 500.0f, 500.0f },
        positionB { 300.0f, 50.0f },
        scaleB { 500.0f, 500.0f },
        colorA { 1.0f, 0.0f, 0.0f, 1.0f },
        colorB { 0.0f, 1.0f, 1.0f, 1.0f },
        textureA("resources/textures/UV test.png"),
        textureB("resources/textures/Wind-waves.png"),
        textureIndexA(0), textureIndexB(1),
        textureASlot(0), textureBSlot(1)
    {

        vertexArray.Generate();
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

    TestBatchRendering::~TestBatchRendering()
    {}

    void TestBatchRendering::OnUpdate(float deltaTime)
    {}

    void TestBatchRendering::OnRender()
    {

        auto quadA = CreateQuad(
            positionA, scaleA, colorA, textureIndexA
        );
        auto quadB = CreateQuad(
            positionB, scaleB, colorB, textureIndexB
        );

        Vertex vertices[8];
        memcpy(
            vertices, quadA.data(),
            quadA.size() * sizeof(Vertex)
        );
        memcpy(
            &vertices[4], quadB.data(),
            quadB.size() * sizeof(Vertex)
        );
        
        vertexBuffer.Bind();
        vertexBuffer.SetData(0, sizeof(vertices), vertices);
        
        indexBuffer.Bind();
        vertexArray.Bind();

        glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;

        program.Bind();
        program.SetUniformMatrix4Floats("u_MVPMatrix", mvpMatrix);

        int textureSamplers[2] = { 0, 1 };
        program.SetUniform1IntArray("u_Textures", 2, textureSamplers);

        Renderer::Draw(vertexArray, indexBuffer, program, 12);

    }

    void TestBatchRendering::OnImGuiRender()
    {
        
        ImGui::SeparatorText("Object A");
        ImGui::SliderFloat2(
            "Position A", &positionA.x,
            -(float)windowWidth/2, (float)windowWidth/2
        );
        ImGui::SliderFloat2(
            "Scale A", &scaleA.x,
            -(float)windowWidth, (float)windowWidth
        );
        ImGui::ColorEdit4("Color A", &colorA.x);
        ImGui::InputInt("Texture Index A", &textureIndexA);
        
        ImGui::SeparatorText("Object B");
        ImGui::SliderFloat2(
            "Translation B", &positionB.x,
            -(float)windowWidth/2, (float)windowWidth/2
        );
        ImGui::SliderFloat2(
            "Scale B", &scaleB.x,
            -(float)windowWidth, (float)windowWidth
        );
        ImGui::ColorEdit4("Color B", &colorB.x);
        ImGui::InputInt("Texture Index B", &textureIndexB);

    }

}