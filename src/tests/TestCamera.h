#pragma once

#include "src/Texture.h"
#include "src/Vertex3D.h"
#include "src/Mesh.h"
#include "src/Camera.h"

#include "Test.h"

namespace tests
{

    class TestCamera : public Test
    {

    public:

        Camera camera;

        TestCamera();
        ~TestCamera() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        void WindowInit(GLFWwindow *window) override;
        void ProcessInput(GLFWwindow *window) override;

    private:

        float deltaTime;

        int windowWidth;
        int windowHeight;

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

        ShaderProgram program;

    };

};