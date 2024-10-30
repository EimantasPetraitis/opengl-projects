#include "Mesh.h"

#include <algorithm>
#include <iterator>

Mesh::Mesh(
    MeshVertex *meshVertices, unsigned int vertexCount,
    unsigned int* indices, unsigned int indexCount,
    Texture* texture, Vector4 color
)
    : vertices(meshVertices),
    vertexCount(vertexCount),
    indices(indices), indexCount(indexCount),
    texture(texture), color(color)
{}

Mesh::Mesh(
    MeshVertex *meshVertices, unsigned int vertexCount,
    unsigned int* indices, unsigned int indexCount,
    Vector4 color
)
    : vertices(meshVertices),
    vertexCount(vertexCount),
    indices(indices), indexCount(indexCount),
    texture(nullptr), color(color)
{}

Mesh::Mesh()
    : vertices(nullptr),
    vertexCount(0),
    indices(nullptr), indexCount(0),
    texture(nullptr),
    color(Vector4{ 1.0f, 1.0f, 1.0f, 1.0f })
{}

Mesh::~Mesh()
{

    //

}

void Mesh::SetVertices(
    MeshVertex *meshVertices, unsigned int vertexCount
)
{

    this->vertices = meshVertices;
    this->vertexCount = vertexCount;

}

void Mesh::SetIndices(
    unsigned int *indices, unsigned int indexCount
)
{

    this->indices = indices;
    this->indexCount = indexCount;

}

void Mesh::SetTexture(Texture* texture)
{

    this->texture = texture;

}

void Mesh::SetColor(Vector4 color)
{

    this->color = color;

}

MeshVertex *Mesh::GetVertices()
{

    MeshVertex* vertexArray = new MeshVertex[vertexCount];

    std::copy(
        vertices, vertices + vertexCount,
        vertexArray
    );

    return vertexArray;

}

Vertex3D *Mesh::GetVertex3DArray(int textureSlot)
{

    Vertex3D* vertex3DArray = new Vertex3D[vertexCount];

    for (int i = 0; i < vertexCount; i++)
    {

        Vertex3D thisVertex3D(
            vertices[i].position,
            color, vertices[i].textureCoordinates,
            (float)textureSlot
        );
        vertex3DArray[i] = thisVertex3D;

    }

    return vertex3DArray;

}

Vector3* Mesh::GetVertexPositionArray()
{

    Vector3* vertexPositionArray = new Vector3[vertexCount];

    for (int i = 0; i < vertexCount; i++)
    {
        vertexPositionArray[i] = vertices[i].position;
    }

    return vertexPositionArray;

}

PosNormalVertex *Mesh::GetPosNormalVertexArray()
{

    PosNormalVertex* vertexArray = new PosNormalVertex[vertexCount];

    for (int i = 0; i < vertexCount; i++)
    {

        PosNormalVertex vertex(
            vertices[i].position, vertices[i].normal
        );
        vertexArray[i] = vertex;

    }

    return vertexArray;
}

unsigned int *Mesh::GetIndices()
{

    unsigned int* indicesArray = new unsigned int[indexCount];
    
    for (int i = 0; i < indexCount; i++)
    {
        indicesArray[i] = indices[i];
    }
    
    return indicesArray;

}

Texture* Mesh::GetTexture()
{
    
    return texture;

}