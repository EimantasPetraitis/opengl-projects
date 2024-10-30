#include "TestCamera.h"

#include <GL/glew.h>
#include <imgui.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "src/Cube.h"

namespace tests
{

    TestCamera::TestCamera()
        : deltaTime(0.0f),
        windowWidth(1280),
        windowHeight(960),
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
        program(
            "resources/shaders/basic3D.vert",
            "resources/shaders/basic3D.frag"
        )
    {

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glEnable(GL_DEPTH_TEST);

        Mesh mesh = Cube();

        mesh.SetColor(Vector4{ 1.0f, 1.0f, 1.0f, 1.0f });
        mesh.SetTexture(&texture);

        Vertex3D* vertices = mesh.GetVertex3DArray(0);
        vertexBuffer.Generate(
            mesh.GetVertexCount() * sizeof(Vertex3D), vertices
        );
        delete[] vertices;

        unsigned int* indices = mesh.GetIndices();
        indexBuffer.Generate(
            indices,
            mesh.GetIndexCount() * sizeof(unsigned int),
            mesh.GetIndexCount()
        );
        delete[] indices;

        VertexBufferLayout layout = Vertex3D::getLayout();
        
        vertexArray.Generate();
        vertexArray.AddBuffer(vertexBuffer, layout);

        program.Bind();
        mesh.GetTexture()->Bind(0);

        mesh.DeleteVertices();

    }

    TestCamera::~TestCamera()
    {}

    void TestCamera::OnUpdate(float deltaTime)
    {

        this->deltaTime = deltaTime;
        
        Vector3 newAxis = Vector3{ 1.0f, 1.0f, 2.0f };
        newAxis.Normalize();
        rotationAxis = newAxis;
        rotation += 30.0f * deltaTime;

    }

    void TestCamera::OnRender()
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::Clear();

        indexBuffer.Bind();
        vertexArray.Bind();
        program.Bind();

        Vector3 positions[10] = {
            Vector3{  0.0f,  0.0f,  0.0f },
            Vector3{ -1.9f,  1.5f,  1.4f },
            Vector3{  0.6f,  0.3f, -0.9f },
            Vector3{ -0.9f,  1.3f, -1.0f },
            Vector3{ -2.9f, -0.3f,  1.1f },
            Vector3{  1.2f,  0.0f,  0.4f },
            Vector3{  1.3f,  1.8f,  0.4f },
            Vector3{ -0.8f,  2.3f,  1.7f },
            Vector3{ -2.2f, -2.2f,  1.6f },
            Vector3{  0.8f, -1.8f,  0.2f }
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

        program.SetUniform1Int(
            "u_Texture", 0
        );

        for (int i = 0; i < 10; i++)
        {

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, positions[i].GLMVector());

            float cubeRotation = 20.0f * i;
            if ((i % 2) == 0)
                cubeRotation += rotation;

            model = glm::rotate(
                model, glm::radians(cubeRotation),
                rotationAxis.GLMVector()
            );
            model = glm::scale(model, scale.GLMVector());

            program.SetUniformMatrix4Floats(
                "u_Model", model
            );

            Renderer::Draw(
                vertexArray, indexBuffer, program
            );

        }

    }

    void TestCamera::OnImGuiRender()
    {}

    void TestCamera::WindowInit(GLFWwindow *window)
    {

        camera.InitializeInput(window);

    }

    void TestCamera::ProcessInput(GLFWwindow *window)
    {

        camera.ProcessInput(window, deltaTime);

    }

}