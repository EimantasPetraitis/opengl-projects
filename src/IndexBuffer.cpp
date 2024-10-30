#include "IndexBuffer.h"

unsigned int *CalculateQuadIndices(unsigned int indicesCount)
{

    unsigned int* indices = new unsigned int[indicesCount];

    int offset = 0;
    
    for (int i = 0; i < indicesCount; i += 6)
    {

        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;

    }

    return indices;

}

IndexBuffer::IndexBuffer(
    const void* data, unsigned int bufferSize,
    unsigned int elementCount
)
    : id(0), size(bufferSize), count(elementCount)
{

    Generate(data, size, count);

}

IndexBuffer::IndexBuffer()
    : id(0), size(0), count(0)
{}

IndexBuffer::~IndexBuffer()
{

    if (id != 0)
        glDeleteBuffers(1, &id);

}

void IndexBuffer::Generate(
    const void *data, unsigned int bufferSize,
    unsigned int elementCount
)
{

    size = bufferSize;
    count = elementCount;

    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

void IndexBuffer::Bind() const
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);

}

void IndexBuffer::Unbind() const
{

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}