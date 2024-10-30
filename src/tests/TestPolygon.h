#pragma once

#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/VertexBufferLayout.h"
#include "src/VertexArray.h"
#include "src/ShaderProgram.h"

#include "Test.h"

namespace tests
{

    class TestPolygon : public Test
    {

    public:

        TestPolygon();
        ~TestPolygon() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:

        float vertices[8];
        unsigned int indices[6];

        float color[4];

        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        VertexBufferLayout layout;
        VertexArray vertexArray;

        ShaderProgram program;

        int windowWidth;
        int windowHeight;

    };

};