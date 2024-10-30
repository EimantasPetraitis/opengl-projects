#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include "src/VertexBuffer.h"
#include "src/IndexBuffer.h"
#include "src/VertexBufferLayout.h"
#include "src/VertexArray.h"
#include "src/ShaderProgram.h"
#include "src/Texture.h"

#include "Test.h"

namespace tests
{

    class TestTexture : public Test
    {

    public:

        TestTexture();
        ~TestTexture() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:

        int windowWidth;
        int windowHeight;

        float vertices[16];
        unsigned int indices[6];

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

        glm::vec3 translationA;
        glm::vec3 scaleA;
        glm::vec3 translationB;
        glm::vec3 scaleB;

    };

};