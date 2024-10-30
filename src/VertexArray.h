#pragma once

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{

private:

    unsigned int id;

public:

    VertexArray();
    ~VertexArray();

    void Generate();

    void AddBuffer(
        const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout
    );

    void Bind() const;

    void Unbind() const;

};