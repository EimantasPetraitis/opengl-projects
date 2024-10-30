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

    class TestBatchRendererGrid : public Test
    {

    public:

        TestBatchRendererGrid();
        ~TestBatchRendererGrid() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:

        int windowWidth;
        int windowHeight;

        ShaderProgram program;

        Texture textureA;
        Texture textureB;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        Vector2 cornerPosition;
        Vector2 squareScale;

    };

};