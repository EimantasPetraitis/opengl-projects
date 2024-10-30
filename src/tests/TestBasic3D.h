#pragma once

#include "src/Texture.h"
#include "src/Vertex3D.h"
#include "src/Mesh.h"

#include "Test.h"

namespace tests
{

    class TestBasic3D : public Test
    {

    public:

        TestBasic3D();
        ~TestBasic3D() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:

        int windowWidth;
        int windowHeight;

        Vector3 position;
        Vector3 scale;
        Vector3 rotationAxis;
        float rotation;

        Mesh mesh;

        Texture texture;
        int textureSlot;

        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        VertexBufferLayout layout;
        VertexArray vertexArray;

        ShaderProgram program;

    };

};