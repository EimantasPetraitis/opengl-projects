#include "Cube.h"

#include "IndexBuffer.h"

Mesh Cube()
{

    Mesh mesh;

    const unsigned int quadCount = 6;
        
    MeshVertex* vertices = new MeshVertex[quadCount * 4] {

        MeshVertex{ Vector3{-0.5f, -0.5f, -0.5f}, Vector2{0.0f, 0.0f}, Vector3{  0.0f,  0.0f, -1.0f } },
        MeshVertex{ Vector3{ 0.5f, -0.5f, -0.5f}, Vector2{1.0f, 0.0f}, Vector3{  0.0f,  0.0f, -1.0f } },
        MeshVertex{ Vector3{ 0.5f,  0.5f, -0.5f}, Vector2{1.0f, 1.0f}, Vector3{  0.0f,  0.0f, -1.0f } },
        MeshVertex{ Vector3{-0.5f,  0.5f, -0.5f}, Vector2{0.0f, 1.0f}, Vector3{  0.0f,  0.0f, -1.0f } },

        MeshVertex{ Vector3{-0.5f, -0.5f,  0.5f}, Vector2{0.0f, 0.0f}, Vector3{  0.0f,  0.0f,  1.0f } },
        MeshVertex{ Vector3{ 0.5f, -0.5f,  0.5f}, Vector2{1.0f, 0.0f}, Vector3{  0.0f,  0.0f,  1.0f } },
        MeshVertex{ Vector3{ 0.5f,  0.5f,  0.5f}, Vector2{1.0f, 1.0f}, Vector3{  0.0f,  0.0f,  1.0f } },
        MeshVertex{ Vector3{-0.5f,  0.5f,  0.5f}, Vector2{0.0f, 1.0f}, Vector3{  0.0f,  0.0f,  1.0f } },

        MeshVertex{ Vector3{-0.5f,  0.5f,  0.5f}, Vector2{1.0f, 0.0f}, Vector3{ -1.0f,  0.0f,  0.0f } },
        MeshVertex{ Vector3{-0.5f,  0.5f, -0.5f}, Vector2{1.0f, 1.0f}, Vector3{ -1.0f,  0.0f,  0.0f } },
        MeshVertex{ Vector3{-0.5f, -0.5f, -0.5f}, Vector2{0.0f, 1.0f}, Vector3{ -1.0f,  0.0f,  0.0f } },
        MeshVertex{ Vector3{-0.5f, -0.5f,  0.5f}, Vector2{0.0f, 0.0f}, Vector3{ -1.0f,  0.0f,  0.0f } },

        MeshVertex{ Vector3{ 0.5f,  0.5f,  0.5f}, Vector2{1.0f, 0.0f}, Vector3{  1.0f,  0.0f,  0.0f } },
        MeshVertex{ Vector3{ 0.5f,  0.5f, -0.5f}, Vector2{1.0f, 1.0f}, Vector3{  1.0f,  0.0f,  0.0f } },
        MeshVertex{ Vector3{ 0.5f, -0.5f, -0.5f}, Vector2{0.0f, 1.0f}, Vector3{  1.0f,  0.0f,  0.0f } },
        MeshVertex{ Vector3{ 0.5f, -0.5f,  0.5f}, Vector2{0.0f, 0.0f}, Vector3{  1.0f,  0.0f,  0.0f } },

        MeshVertex{ Vector3{-0.5f, -0.5f, -0.5f}, Vector2{0.0f, 1.0f}, Vector3{  0.0f, -1.0f,  0.0f } },
        MeshVertex{ Vector3{ 0.5f, -0.5f, -0.5f}, Vector2{1.0f, 1.0f}, Vector3{  0.0f, -1.0f,  0.0f } },
        MeshVertex{ Vector3{ 0.5f, -0.5f,  0.5f}, Vector2{1.0f, 0.0f}, Vector3{  0.0f, -1.0f,  0.0f } },
        MeshVertex{ Vector3{-0.5f, -0.5f,  0.5f}, Vector2{0.0f, 0.0f}, Vector3{  0.0f, -1.0f,  0.0f } },

        MeshVertex{ Vector3{-0.5f,  0.5f, -0.5f}, Vector2{0.0f, 1.0f}, Vector3{  0.0f,  1.0f,  0.0f } },
        MeshVertex{ Vector3{ 0.5f,  0.5f, -0.5f}, Vector2{1.0f, 1.0f}, Vector3{  0.0f,  1.0f,  0.0f } },
        MeshVertex{ Vector3{ 0.5f,  0.5f,  0.5f}, Vector2{1.0f, 0.0f}, Vector3{  0.0f,  1.0f,  0.0f } },
        MeshVertex{ Vector3{-0.5f,  0.5f,  0.5f}, Vector2{0.0f, 0.0f}, Vector3{  0.0f,  1.0f,  0.0f } }

    };
    mesh.SetVertices(vertices, quadCount * 4);

    unsigned int* indices
        = CalculateQuadIndices(quadCount * 6);
    mesh.SetIndices(indices, quadCount * 6);

    return mesh;

}