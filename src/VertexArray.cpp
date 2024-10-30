#include "VertexArray.h"

VertexArray::VertexArray()
    : id(0)
{}

VertexArray::~VertexArray()
{

    glDeleteVertexArrays(1, &id);

}

void VertexArray::Generate()
{

    glGenVertexArrays(1, &id);

}

void VertexArray::AddBuffer(
    const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout
)
{

    Bind();
    vertexBuffer.Bind();

    const std::vector<VertexBufferLayoutElement> elements
        = layout.GetElements();
    intptr_t offset = 0;

    for (int i = 0; i < elements.size(); i++)
    {

        VertexBufferLayoutElement element = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i, element.count, element.type, element.normalized,
            layout.GetStride(), (const void*)offset
        );

        offset +=
            element.count
            * VertexBufferLayoutElement::GetTypeSize(element.type);

    }

}

void VertexArray::Bind() const
{
    
    glBindVertexArray(id);

}

void VertexArray::Unbind() const
{

    glBindVertexArray(0);

}