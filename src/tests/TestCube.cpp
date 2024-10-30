#include "TestCube.h"

#include <GL/glew.h>
#include <imgui.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "src/Cube.h"

namespace tests
{

    TestCube::TestCube()
        : windowWidth(1280),
        windowHeight(960),
        position { 0.0f, 0.0f, 0.0f },
        scale { 1.0f, 1.0f, 1.0f },
        rotationAxis { 0.0f, 1.0f, 0.0f },
        rotation(0.0f),
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
        mesh.DeleteIndices();

    }

    TestCube::~TestCube()
    {}

    void TestCube::OnUpdate(float deltaTime)
    {

        Vector3 newAxis = Vector3{1.0f, 2.0f, 1.0f};
        newAxis.Normalize();
        rotationAxis = newAxis;

        rotation += 30.0f * deltaTime;

    }

    void TestCube::OnRender()
    {

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        Renderer::Clear();

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
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

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

    void TestCube::OnImGuiRender()
    {

        //

    }

}