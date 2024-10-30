#pragma once

#include "VertexBufferLayout.h"
#include "Vector.h"

struct Vertex
{

    Vector2 position;
    Vector4 color;
    Vector2 textureCoordinates;
    float textureIndex;

    static VertexBufferLayout getLayout()
    {

        VertexBufferLayout layout;

        layout.Push(GL_FLOAT, 2, false);  // Position
        layout.Push(GL_FLOAT, 4, false);  // Color
        layout.Push(GL_FLOAT, 2, false);  // Texture coordinates
        layout.Push(GL_FLOAT, 1, false);  // Texture index

        return layout;

    }

};