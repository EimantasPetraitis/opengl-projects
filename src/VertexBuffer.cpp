#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(
    unsigned int size, bool isDynamic /* = false*/
)
    : id(0), dynamic(false)
{

    Generate(size, isDynamic);

}

VertexBuffer::VertexBuffer(
    unsigned int size, const void* data,
    bool isDynamic /*= false*/
)
    : id(0), dynamic(false)
{

    Generate(size, data, isDynamic);

}

VertexBuffer::VertexBuffer()
    : id(0), dynamic(false)
{}

VertexBuffer::~VertexBuffer()
{

    if (id != 0)
        glDeleteBuffers(1, &id);

}

void VertexBuffer::Generate(
    unsigned int size, bool isDynamic /*= false*/
)
{

    dynamic = isDynamic;
    GLenum usage;

    if (dynamic)
        usage = GL_DYNAMIC_DRAW;
    else
        usage = GL_STATIC_DRAW;

    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage);

}

void VertexBuffer::Generate(
    unsigned int size, const void* data,
    bool isDynamic /*= false*/
)
{

    dynamic = isDynamic;
    GLenum usage;

    if (dynamic)
        usage = GL_DYNAMIC_DRAW;
    else
        usage = GL_STATIC_DRAW;
    
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);

}

void VertexBuffer::Bind() const
{

    glBindBuffer(GL_ARRAY_BUFFER, id);

}

void VertexBuffer::Unbind() const
{

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void VertexBuffer::SetData(int offset, int size, void* data)
{

    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);

}