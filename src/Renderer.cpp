#include "Renderer.h"

void GLAPIENTRY HandleOpenGLErrors(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght,
    const GLchar* message, const void* userParam
)
{

    std::cout << "[OpenGL Error]  " << "type: " << type << "  id: " << id
        << "  severity: " << severity << "\n" << message << "\n\n\n";
    
    exit(-1);

}

void Renderer::EnableDebuging()
{

    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(HandleOpenGLErrors, nullptr);

}

void Renderer::Draw(
    const VertexArray& vertexArray,
    const IndexBuffer& indexBuffer,
    const ShaderProgram& shader
)
{

    vertexArray.Bind();
    indexBuffer.Bind();
    shader.Bind();

    glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);

}

void Renderer::Draw(
    const VertexArray& vertexArray,
    const IndexBuffer& indexBuffer,
    const ShaderProgram& shader,
    const unsigned int numIndices
)
{

    vertexArray.Bind();
    indexBuffer.Bind();
    shader.Bind();

    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, nullptr);

}

void Renderer::Clear()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

}