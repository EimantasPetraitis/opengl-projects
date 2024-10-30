#pragma once

#include "Texture.h"
#include "Vertex3D.h"
#include "MeshVertex.h"
#include "PosNormalVertex.h"

class Mesh
{

public:

    Mesh(
        MeshVertex* meshVertices, unsigned int vertexCount,
        unsigned int* indices, unsigned int indexCount,
        Texture* texture,
        Vector4 color = Vector4{1.0f, 1.0f, 1.0f, 1.0f}
    );
    Mesh(
        MeshVertex* meshVertices, unsigned int vertexCount,
        unsigned int* indices, unsigned int indexCount,
        Vector4 color
    );
    Mesh();

    ~Mesh();

    void SetVertices(
        MeshVertex* meshVertices, unsigned int vertexCount
    );
    void SetIndices(
        unsigned int* indices, unsigned int indexCount
    );
    void SetTexture(Texture* texture);
    void SetColor(Vector4 color);

    MeshVertex* GetVertices();
    Vertex3D* GetVertex3DArray(int textureSlot);
    Vector3* GetVertexPositionArray();
    PosNormalVertex* GetPosNormalVertexArray();

    inline unsigned int GetVertexCount() { return vertexCount; };
    unsigned int* GetIndices();
    inline unsigned int GetIndexCount() { return indexCount; };
    Texture* GetTexture();

    inline void DeleteVertices() { delete[] vertices; };
    inline void DeleteIndices() { delete[] indices; };

private:

    MeshVertex* vertices;
    unsigned int vertexCount;

    unsigned int* indices;
    unsigned int indexCount;

    Texture* texture;
    Vector4 color;

};