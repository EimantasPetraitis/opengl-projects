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

    class TestBatchRendering : public Test
    {

    public:

        TestBatchRendering();
        ~TestBatchRendering() override;

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

        Vector2 positionA;
        Vector2 scaleA;
        Vector2 positionB;
        Vector2 scaleB;

        Vector4 colorA;
        Vector4 colorB;
        int textureIndexA;
        int textureIndexB;

    };

};