#include "TestTexture.h"

#include <GL/glew.h>
#include <imgui.h>

namespace tests
{

    TestTexture::TestTexture()
        : windowWidth(1280),
        windowHeight(960),
        vertices
        {
            -50.0f, -50.0f, 0.0f, 0.0f,
             50.0f, -50.0f, 1.0f, 0.0f,
             50.0f,  50.0f, 1.0f, 1.0f,
            -50.0f,  50.0f, 0.0f, 1.0f
        },
        indices
        {
            0, 1, 2,
            2, 3, 0
        },
        vertexBuffer(4 * 4 * sizeof(float), vertices),
        indexBuffer(indices, 6 * sizeof(unsigned int), 6),
        program
        (
            "resources/shaders/basic.vert",
            "resources/shaders/basic.frag"
        ),
        translationA(0, 0, 0),
        scaleA(1, 1, 1),
        translationB(0, 0, 0),
        scaleB(1, 1, 1),
        textureA("resources/textures/UV test.png"),
        textureB("resources/textures/Wind-waves.png"),
        textureASlot(0), textureBSlot(1)
    {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        layout.Push(GL_FLOAT, 2, false);
        layout.Push(GL_FLOAT, 2, false);
        vertexArray.Generate();
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

    TestTexture::~TestTexture()
    {}

    void TestTexture::OnUpdate(float deltaTime)
    {}

    void TestTexture::OnRender()
    {

        indexBuffer.Bind();
        vertexArray.Bind();
        program.Bind();

        {

            glm::mat4 modelMatrix = glm::scale(
                glm::translate(glm::mat4(1.0f), translationA),
                scaleA
            );
            glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

            program.Bind();
            program.SetUniformMatrix4Floats("u_MVPMatrix", mvpMatrix);
            program.SetUniform1Int("u_Texture", textureASlot);

            Renderer::Draw(vertexArray, indexBuffer, program);
        
        }
        {

            glm::mat4 modelMatrix = glm::scale(
                glm::translate(glm::mat4(1.0f), translationB),
                scaleB
            );
            glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;

            program.Bind();
            program.SetUniformMatrix4Floats("u_MVPMatrix", mvpMatrix);
            program.SetUniform1Int("u_Texture", textureBSlot);

            Renderer::Draw(vertexArray, indexBuffer, program);
        
        }

    }

    void TestTexture::OnImGuiRender()
    {

        ImGui::SliderFloat3(
            "Translation A", &translationA.x,
            -(float)windowWidth/2, (float)windowWidth/2
        );
        ImGui::SliderFloat3(
            "Scale A", &scaleA.x,
            -(float)windowWidth/200, (float)windowWidth/200
        );
        ImGui::SliderFloat3(
            "Translation B", &translationB.x,
            -(float)windowWidth/2, (float)windowWidth/2
        );
        ImGui::SliderFloat3(
            "Scale B", &scaleB.x,
            -(float)windowWidth/200, (float)windowWidth/200
        );

    }

}