#pragma once

#include "src/Texture.h"
#include "src/Vertex3D.h"
#include "src/Mesh.h"
#include "src/Camera.h"
#include "src/PointLight.h"

#include "Test.h"

namespace tests
{

    class TestLighting : public Test
    {

    public:

        Camera camera;

        TestLighting();
        ~TestLighting() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        void WindowInit(GLFWwindow *window) override;
        void ProcessInput(GLFWwindow *window) override;

    private:

        float deltaTime;

        int windowWidth;
        int windowHeight;

        PointLight light;

        Vector3 scale;
        Vector3 rotationAxis;
        float rotation;

        float lastMouseX;
        float lastMouseY;

        Texture texture;
        int textureSlot;

        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        VertexBufferLayout layout;
        VertexArray vertexArray;

        VertexBuffer lightVertexBuffer;
        IndexBuffer lightIndexBuffer;
        VertexArray lightVAO;

        ShaderProgram program;
        ShaderProgram lightProgram;

    };

};