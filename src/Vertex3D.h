#pragma once

#include "VertexBufferLayout.h"
#include "Vector.h"

struct Vertex3D
{

    Vector3 position;
    Vector4 color;
    Vector2 textureCoordinates;
    float textureIndex;

    Vertex3D(
        Vector3 position, Vector4 color,
        Vector2 textureCoordinates, float textureIndex
    )
        : position(position),
        color(color),
        textureCoordinates(textureCoordinates),
        textureIndex(textureIndex)
    {}

    Vertex3D()
        : position(Vector3{ 0.0f, 0.0f, 0.0f} ),
        color(Vector4{ 1.0f, 1.0f, 1.0f, 1.0f }),
        textureCoordinates(Vector2{ 0.0f, 0.0f }),
        textureIndex(-1.0f)
    {}

    static VertexBufferLayout getLayout()
    {

        VertexBufferLayout layout;

        layout.Push(GL_FLOAT, 3, false);  // Position
        layout.Push(GL_FLOAT, 4, false);  // Color
        layout.Push(GL_FLOAT, 2, false);  // Texture coordinates
        layout.Push(GL_FLOAT, 1, false);  // Texture index

        return layout;

    }

};