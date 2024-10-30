#pragma once

#include "VertexBufferLayout.h"
#include "Vector.h"

struct MeshVertex
{

    Vector3 position;
    Vector2 textureCoordinates;
    Vector3 normal { 0.0f, 0.0f, 0.0f };

    static VertexBufferLayout getLayout()
    {

        VertexBufferLayout layout;

        layout.Push(GL_FLOAT, 3, false);  // Position
        layout.Push(GL_FLOAT, 2, false);  // Texture coordinates
        layout.Push(GL_FLOAT, 3, false);  // Normal

        return layout;

    }

};