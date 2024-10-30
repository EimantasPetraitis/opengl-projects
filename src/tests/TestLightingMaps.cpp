#include "TestLightingMaps.h"

#include <GL/glew.h>
#include <imgui.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "src/Cube.h"

namespace tests
{

    TestLightingMaps::TestLightingMaps()
        : deltaTime(0.0f),
        windowWidth(1280),
        windowHeight(960),
        lights {},
        directionalLight(),
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
        diffuseMap("resources/textures/Container-diffuse.png"),
        diffuseMapSlot(1),
        specularMap("resources/textures/Container-specular.png"),
        specularMapSlot(2),
        emissionMap("resources/textures/Container-emission.png"),
        emissionMapSlot(3),
        vertexBuffer(),
        indexBuffer(),
        lightVertexBuffer(),
        lightIndexBuffer(),
        program(
            "resources/shaders/3D lit.vert",
            "resources/shaders/3D lit.frag"
        ),
        lightProgram(
            "resources/shaders/3D light source texture coordinates.vert",
            "resources/shaders/3D light source.frag"
        )
    {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glEnable(GL_DEPTH_TEST);

        lights[0].position = glm::vec3(1.8f, 1.0f, 0.2f);
        lights[0].constant = 1.0f;
        lights[0].linear = 0.22f;
        lights[0].quadratic = 0.20f;

        lights[1].position = glm::vec3(-0.8f, -0.4f, 1.2f);
        lights[1].diffuse = glm::vec3(0.9f, 0.3f, 0.1f);
        lights[1].ambient = lights[1].diffuse * 0.1f;

        lights[2].position = glm::vec3(-1.4f, 0.4f, -0.9f);
        lights[2].diffuse = glm::vec3(0.0f, 0.1f, 0.6f);
        lights[2].ambient = lights[2].diffuse * 0.1f;

        directionalLight.diffuse = glm::vec3(1.0f, 0.9f, 0.6f);
        directionalLight.ambient = directionalLight.diffuse * 0.1f;
        directionalLight.specular = glm::vec3(1.0f);

        Mesh mesh = Cube();

        mesh.SetColor(Vector4{ 1.0f, 1.0f, 1.0f, 1.0f });
        mesh.SetTexture(&diffuseMap);

        // Normal VAO
        
        MeshVertex* vertices = mesh.GetVertices();
        vertexBuffer.Generate(
            mesh.GetVertexCount() * sizeof(MeshVertex),
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

        VertexBufferLayout layout = MeshVertex::getLayout();
        
        vertexArray.Generate();
        vertexArray.AddBuffer(vertexBuffer, layout);

        // Light source VAO

        lightIndexBuffer = indexBuffer;

        VertexBufferLayout lightLayout = MeshVertex::getLayout();
        
        lightVAO.Generate();
        lightVAO.Bind();
        lightVAO.AddBuffer(
            vertexBuffer, lightLayout
        );

        // Programs

        program.Bind();

        mesh.DeleteVertices();
        mesh.DeleteIndices();

    }

    TestLightingMaps::~TestLightingMaps()
    {}

    void TestLightingMaps::OnUpdate(float deltaTime)
    {

        this->deltaTime = deltaTime;
        
        Vector3 newAxis = Vector3{ 1.0f, 1.0f, 2.0f };
        newAxis.Normalize();
        rotationAxis = newAxis;
        rotation += 30.0f * deltaTime;

        lights[0].position.y = 1.0f + sin(glfwGetTime());

        lights[0].diffuse.x = 0.5f + sin(glfwGetTime() * 2.0f) / 2;
        lights[0].diffuse.y = 0.5f + sin(glfwGetTime() * 0.7f) / 2;
        lights[0].diffuse.z = 0.5f + sin(glfwGetTime() * 1.3f) / 2;

        lights[0].ambient = lights[1].diffuse * 0.1f;

    }

    void TestLightingMaps::OnRender()
    {

        glClearColor(0.02f, 0.02f, 0.05f, 1.0f);
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
        
        Material defaultMaterial(
            &diffuseMap, &specularMap, 128.0f,
            &emissionMap, 0.0f
        );
        
        Material glowingMaterial(
            &diffuseMap, &specularMap, 128.0f,
            &emissionMap, 0.5f
        );

        diffuseMap.Bind(diffuseMapSlot);
        specularMap.Bind(specularMapSlot);
        emissionMap.Bind(emissionMapSlot);

        for (int i = 0; i < NUM_POINT_LIGHTS; i++)
        {
            program.SetUniformPointLight(
                "u_PointLights[" + std::to_string(i) + "]",
                lights[i]
            );
        }

        program.SetUniformDirectionalLight(
            "u_DirectionalLight", directionalLight
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

            if (i == 4)
            {
                program.SetUniformMaterial(
                    "u_Material", glowingMaterial,
                    diffuseMapSlot, specularMapSlot, emissionMapSlot
                );
            }
            else
            {
                program.SetUniformMaterial(
                    "u_Material", defaultMaterial,
                    diffuseMapSlot, specularMapSlot, emissionMapSlot
                );
            }

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

        for (int i = 0; i < NUM_POINT_LIGHTS; i++)
        {
        
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, lights[i].position);
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
                "u_Color", lights[i].diffuse
            );

            Renderer::Draw(
                lightVAO, lightIndexBuffer, lightProgram
            );

        }

    }

    void TestLightingMaps::OnImGuiRender()
    {}

    void TestLightingMaps::WindowInit(GLFWwindow *window)
    {

        camera.InitializeInput(window);

    }

    void TestLightingMaps::ProcessInput(GLFWwindow *window)
    {

        camera.ProcessInput(window, deltaTime);

    }

}