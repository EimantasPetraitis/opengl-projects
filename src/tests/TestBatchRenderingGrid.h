#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/VertexBufferLayout.h"
#include "src/VertexArray.h"
#include "src/ShaderProgram.h"
#include "src/Texture.h"

#include "src/Vector.h"
#include "src/Vertex.h"

#include "Test.h"

namespace tests
{

    class TestBatchRenderingGrid : public Test
    {

    public:

        TestBatchRenderingGrid();
        ~TestBatchRenderingGrid() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:

        int windowWidth;
        int windowHeight;

        const unsigned int maxQuadCount;
        const unsigned int maxVertexCount;
        const unsigned int maxIndexCount;

        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        VertexBufferLayout layout;
        VertexArray vertexArray;

        ShaderProgram program;

        Texture textureA;
        Texture textureB;

        unsigned int textureASlot;
        unsigned int textureBSlot;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        Vector2 cornerPosition;
        Vector2 squareScale;

        Vector4 colorWhite;
        Vector4 colorBlack;
        int textureIndexWhite;
        int textureIndexBlack;

    };

};