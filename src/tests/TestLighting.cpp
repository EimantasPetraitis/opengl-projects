#include "TestLighting.h"

#include <GL/glew.h>
#include <imgui.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "src/Cube.h"
#include "src/MaterialPlain.h"

namespace tests
{

    TestLighting::TestLighting()
        : deltaTime(0.0f),
        windowWidth(1280),
        windowHeight(960),
        light(),
        camera(
            {
                .position = glm::vec3(0.0f, 0.0f, 8.0f),
                .yaw = -90.0f,
                .zoomInputEnabled = true,
                .cameraSpeed = 2.4f
            }
        ),
        lastMouseX(windowWidth / 2),
        lastMouseY(windowHeight / 2),
        scale { 1.0f, 1.0f, 1.0f },
        rotationAxis { 0.0f, 1.0f, 0.0f },
        rotation(-30.0f),
        texture("resources/textures/UV test.png"),
        vertexBuffer(),
        indexBuffer(),
        lightVertexBuffer(),
        lightIndexBuffer(),
        program(
            "resources/shaders/basic 3D lit.vert",
            "resources/shaders/basic 3D lit.frag"
        ),
        lightProgram(
            "resources/shaders/3D light source.vert",
            "resources/shaders/3D light source.frag"
        )
    {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glEnable(GL_DEPTH_TEST);

        light.position = glm::vec3(-1.2f, 0.0f, 0.2f);

        Mesh mesh = Cube();

        mesh.SetColor(Vector4{ 1.0f, 1.0f, 1.0f, 1.0f });
        mesh.SetTexture(&texture);

        // Normal VAO
        
        PosNormalVertex* vertices = mesh.GetPosNormalVertexArray();
        vertexBuffer.Generate(
            mesh.GetVertexCount() * sizeof(PosNormalVertex),
            vertices
        );
        delete[] vertices;

        unsigned int* indices = mesh.GetIndices();
        indexBuffer.Generate(
            indices,
            mesh.GetIndexCount() * sizeof(unsigned int),
            mesh.GetIndexCount()
        );
        delete[] indices;

        VertexBufferLayout layout = PosNormalVertex::getLayout();
        
        vertexArray.Generate();
        vertexArray.AddBuffer(vertexBuffer, layout);

        // Light source VAO

        lightIndexBuffer = indexBuffer;

        VertexBufferLayout lightLayout;
        lightLayout.Push(GL_FLOAT, 3, false);
        lightLayout.Push(GL_FLOAT, 3, false);
        
        lightVAO.Generate();
        lightVAO.Bind();
        lightVAO.AddBuffer(
            vertexBuffer, lightLayout
        );

        // Programs

        program.Bind();
        mesh.GetTexture()->Bind(0);

        mesh.DeleteVertices();
        mesh.DeleteIndices();

    }

    TestLighting::~TestLighting()
    {}

    void TestLighting::OnUpdate(float deltaTime)
    {

        this->deltaTime = deltaTime;
        
        Vector3 newAxis = Vector3{ 1.0f, 1.0f, 2.0f };
        newAxis.Normalize();
        rotationAxis = newAxis;
        rotation += 30.0f * deltaTime;

        light.position.y = sin(glfwGetTime());

        light.diffuse.x = 0.5f + sin(glfwGetTime() * 2.0f) / 2;
        light.diffuse.y = 0.5f + sin(glfwGetTime() * 0.7f) / 2;
        light.diffuse.z = 0.5f + sin(glfwGetTime() * 1.3f) / 2;

        light.ambient = light.diffuse;

    }

    void TestLighting::OnRender()
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::Clear();

        indexBuffer.Bind();
        vertexArray.Bind();
        program.Bind();

        Vector3 positions[5] = {
            Vector3{  0.0f,  0.0f,  0.0f },
            Vector3{ -1.9f,  1.5f,  1.4f },
            Vector3{  0.8f,  0.9f, -1.2f },
            Vector3{ -0.8f,  1.3f, -1.0f },
            Vector3{ -2.9f, -0.3f,  1.1f }
        };
        
        glm::mat4 view = camera.ViewMatrix();

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.fov),
            (float)windowWidth/(float)windowHeight,
            0.1f, 100.0f
        );

        program.SetUniformMatrix4Floats(
            "u_View", view
        );
        program.SetUniformMatrix4Floats(
            "u_Projection", projection
        );
        
        MaterialPlain basicMaterial(
            glm::vec3(1.0f, 0.5f, 0.31f),
            glm::vec3(1.0f, 0.5f, 0.31f),
            glm::vec3(0.5f, 0.5f, 0.5f), 32.0f
        );

        MaterialPlain goldMaterial(
            glm::vec3(0.24725f, 0.1995f, 0.0745f),
            glm::vec3(0.75164f, 0.60648f, 0.22648f),
            glm::vec3(0.628281f, 0.555802f, 0.366065f),
            0.4f * 128.0f
        );

        MaterialPlain silverMaterial(
            glm::vec3(0.19225f, 0.19225f, 0.19225f),
            glm::vec3(0.50754f, 0.50754f, 0.50754f),
            glm::vec3(0.508273f, 0.508273f, 0.508273f),
            0.4f * 128.0f
        );

        MaterialPlain obsidianMaterial(
            glm::vec3(0.05375f, 0.05f, 0.06625f),
            glm::vec3(0.18275f, 0.17f, 0.22525f),
            glm::vec3(0.332741f, 0.328634f, 0.346435f),
            0.3f * 128.0f
        );

        program.SetUniformPointLight(
            "u_Light", light, false
        );

        program.SetUniform3Floats(
            "u_ViewerPosition", camera.position
        );

        for (int i = 0; i < 5; i++)
        {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i].GLMVector());

            float cubeRotation = 20.0f * i;
            if ((i % 2) == 0)
                cubeRotation += rotation;

            if ((i % 3) == 0)
                program.SetUniformMaterialPlain(
                    "u_Material", obsidianMaterial
                );
            else if ((i % 3) == 1)
                program.SetUniformMaterialPlain(
                    "u_Material", silverMaterial
                );
            else if ((i % 3) == 2)
                program.SetUniformMaterialPlain(
                    "u_Material", goldMaterial
                );

            model = glm::rotate(
                model, glm::radians(cubeRotation),
                rotationAxis.GLMVector()
            );
            model = glm::scale(model, scale.GLMVector());

            program.SetUniformMatrix4Floats(
                "u_Model", model
            );

            glm::mat3 normalMatrix = glm::mat3(
                glm::transpose(glm::inverse(model))
            );
            program.SetUniformMatrix3Floats(
                "u_NormalMatrix", normalMatrix
            );

            Renderer::Draw(
                vertexArray, indexBuffer, program
            );

        }

        // Render the light source

        lightVAO.Bind();
        lightIndexBuffer.Bind();
        lightProgram.Bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, light.position);
        model = glm::scale(model, glm::vec3(0.5f));

        lightProgram.SetUniformMatrix4Floats(
            "u_View", view
        );
        lightProgram.SetUniformMatrix4Floats(
            "u_Projection", projection
        );
        lightProgram.SetUniformMatrix4Floats(
            "u_Model", model
        );

        lightProgram.SetUniform3Floats(
            "u_Color", light.diffuse
        );

        Renderer::Draw(
            lightVAO, lightIndexBuffer, lightProgram
        );

    }

    void TestLighting::OnImGuiRender()
    {}

    void TestLighting::WindowInit(GLFWwindow *window)
    {

        camera.InitializeInput(window);

    }

    void TestLighting::ProcessInput(GLFWwindow *window)
    {

        camera.ProcessInput(window, deltaTime);

    }

}