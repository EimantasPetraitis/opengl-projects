#pragma once

#include "VertexBufferLayout.h"
#include "Vector.h"

struct PosNormalVertex
{

    Vector3 position;
    Vector3 normal;

    PosNormalVertex(Vector3 position, Vector3 normal)
        : position(position), normal(normal)
    {}

    PosNormalVertex()
        : position(Vector3{ 0.0f, 0.0f, 0.0f }),
        normal(Vector3{ 0.0f, 0.0f, 0.0f })
    {}

    static VertexBufferLayout getLayout()
    {

        VertexBufferLayout layout;

        layout.Push(GL_FLOAT, 3, false);  // Position
        layout.Push(GL_FLOAT, 3, false);  // Normal

        return layout;

    }

};