#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Vector.h"

void GLAPIENTRY HandleOpenGLErrors(
    GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei lenght,
    const GLchar* message, const void* userParam
);

class Renderer
{

public:

    static void EnableDebuging();

    static void Draw(
        const VertexArray& vertexArray,
        const IndexBuffer& indexBuffer,
        const ShaderProgram& shader
    );

    static void Draw(
        const VertexArray& vertexArray,
        const IndexBuffer& indexBuffer,
        const ShaderProgram& shader,
        const unsigned int numIndices
    );
    
    static void Clear();

};