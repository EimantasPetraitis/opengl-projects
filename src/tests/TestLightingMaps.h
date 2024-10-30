#pragma once

#include "src/Texture.h"
#include "src/Vertex3D.h"
#include "src/Mesh.h"
#include "src/Camera.h"
#include "src/PointLight.h"
#include "src/DirectionalLight.h"

#include "Test.h"

#define NUM_POINT_LIGHTS 3

namespace tests
{

    class TestLightingMaps : public Test
    {

    public:

        Camera camera;

        TestLightingMaps();
        ~TestLightingMaps() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        void WindowInit(GLFWwindow *window) override;
        void ProcessInput(GLFWwindow *window) override;

    private:

        float deltaTime;

        int windowWidth;
        int windowHeight;

        PointLight lights[NUM_POINT_LIGHTS];
        DirectionalLight directionalLight;

        Vector3 scale;
        Vector3 rotationAxis;
        float rotation;

        float lastMouseX;
        float lastMouseY;

        Texture diffuseMap;
        int diffuseMapSlot;
        Texture specularMap;
        int specularMapSlot;
        Texture emissionMap;
        int emissionMapSlot;

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