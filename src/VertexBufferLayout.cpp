#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
    : stride(0)
{}

void VertexBufferLayout::Push(
    unsigned int type, unsigned int count, bool normalized
)
{

    elements.push_back(
        {
            type, count,
            (unsigned int)(normalized ? GL_TRUE : GL_FALSE)
        }
    );
    stride += count * VertexBufferLayoutElement::GetTypeSize(type);

}