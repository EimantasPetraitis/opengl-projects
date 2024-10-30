#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Vector.h"
#include "Vertex.h"
#include "Renderer.h"

struct BatchData
{

    const unsigned int maxQuadCount = 900;
    const unsigned int maxVertexCount = maxQuadCount * 4;
    const unsigned int maxIndexCount = maxQuadCount * 6;
    const unsigned int maxTextures = 8;

    Vertex* vertices;
    unsigned int vertexIndex;
    unsigned int indexCount;

    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    VertexBufferLayout layout;
    VertexArray vertexArray;
    ShaderProgram shader;

    std::unordered_map<unsigned int, int> textureSlotLookup;
    int currentTextureSlot;

};

class BatchRenderer
{

public:

    static void Init();
    static void Shutdown();

    static void BeginBatch();
    static void EndBatch();
    static void SendBatch();

    static void SetShader(ShaderProgram& program);

    static void DrawQuad(
        const Vector2& position, const Vector2& scale,
        const Vector4& color
    );
    static void DrawQuad(
        const Vector2& position, const Vector2& scale,
        const Texture& texture,
        const Vector4& color = { 1.0f, 1.0f, 1.0f, 1.0f}
    );

    static BatchData data;

};