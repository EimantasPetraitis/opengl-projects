#include "TestBasic3D.h"

#include <GL/glew.h>
#include <imgui.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

namespace tests
{

    TestBasic3D::TestBasic3D()
        : windowWidth(1280),
        windowHeight(960),
        position { 0.0f, 0.0f, 0.0f },
        scale { 1.0f, 1.0f, 1.0f },
        rotationAxis { 0.0f, 1.0f, 0.0f },
        rotation(90.0f),
        texture("resources/textures/UV test.png"),
        mesh(),
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

        MeshVertex meshVertices[4] = {
            MeshVertex{
                Vector3{-0.5f, -0.5f, 0.0f},
                Vector2{0.0f, 0.0f}
            },
            MeshVertex{
                Vector3{0.5f, -0.5f, 0.0f},
                Vector2{1.0f, 0.0f}
            },
            MeshVertex{
                Vector3{0.5f, 0.5f, 0.0f},
                Vector2{1.0f, 1.0f}
            },
            MeshVertex{
                Vector3{-0.5f, 0.5f, 0.0f},
                Vector2{0.0f, 1.0f}
            },
        };
        mesh.SetVertices(meshVertices, 4);

        unsigned int meshIndices[6] = { 0, 1, 2, 2, 3, 0 };
        mesh.SetIndices(meshIndices, 6);

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

    }

    TestBasic3D::~TestBasic3D()
    {}

    void TestBasic3D::OnUpdate(float deltaTime)
    {}

    void TestBasic3D::OnRender()
    {

        indexBuffer.Bind();
        vertexArray.Bind();
        program.Bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position.GLMVector());
        model = glm::rotate(
            model, glm::radians(rotation), rotationAxis.GLMVector()
        );
        model = glm::scale(model, scale.GLMVector());

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(-0.4f, 0.0f, -1.5f));

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),
            (float)windowWidth/(float)windowHeight,
            0.1f, 100.0f
        );

        program.SetUniformMatrix4Floats(
            "u_Model", model
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

        Renderer::Draw(
            vertexArray, indexBuffer, program
        );

    }

    void TestBasic3D::OnImGuiRender()
    {

        //

    }

}