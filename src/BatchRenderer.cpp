#include "BatchRenderer.h"

static unsigned int CreateQuadInArray(
    Vertex* targetArray, unsigned int index,
    Vector2 position, Vector2 scale, Vector4 color,
    int textureIndex = -1
)
{
    
    targetArray[index].position = {
        position.x - 0.5f * scale.x,
        position.y - 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 0.0f, 0.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    targetArray[index].position = {
        position.x + 0.5f * scale.x,
        position.y - 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 1.0f, 0.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    targetArray[index].position = {
        position.x + 0.5f * scale.x,
        position.y + 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 1.0f, 1.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    targetArray[index].position = {
        position.x - 0.5f * scale.x,
        position.y + 0.5f * scale.y
    };
    targetArray[index].color = color;
    targetArray[index].textureCoordinates = { 0.0f, 1.0f };
    targetArray[index].textureIndex = (float)textureIndex;
    index++;

    return index;

}

BatchData BatchRenderer::data;

void BatchRenderer::Init()
{

    data.vertices
        = new Vertex[data.maxVertexCount];
    data.vertexIndex = 0;
    data.indexCount = 0;
    data.currentTextureSlot = 0;
    data.vertexArray.Generate();

    data.vertexBuffer.Generate(
        data.maxVertexCount * sizeof(Vertex), true
    );

    unsigned int* indices = CalculateQuadIndices(data.maxIndexCount);
    data.indexBuffer.Generate(
        indices, data.maxIndexCount * sizeof(unsigned int),
        data.maxIndexCount
    );
    delete[] indices;

    data.layout = Vertex::getLayout();

    data.vertexArray.AddBuffer(
        data.vertexBuffer, data.layout
    );

}

void BatchRenderer::Shutdown()
{

    delete[] data.vertices;

    data.vertexArray.Unbind();
    data.indexBuffer.Unbind();
    data.shader.Unbind();

}

void BatchRenderer::BeginBatch()
{

    data.vertexIndex = 0;
    data.indexCount = 0;

    data.textureSlotLookup.clear();
    data.currentTextureSlot = 0;

}

void BatchRenderer::EndBatch()
{

    //

}

void BatchRenderer::SendBatch()
{

    data.vertexBuffer.Bind();
    data.vertexBuffer.SetData(
        0, sizeof(Vertex) * data.vertexIndex,
        data.vertices
    );
    
    data.indexBuffer.Bind();
    data.vertexArray.Bind();

    data.shader.Bind();

    int textureSamplers[data.maxTextures];

    for (int i = 0; i < data.maxTextures; i++)
    {
        textureSamplers[i] = i;
    }
    data.shader.SetUniform1IntArray(
        "u_Textures", 2, textureSamplers
    );

    Renderer::Draw(
        data.vertexArray, data.indexBuffer,
        data.shader, data.indexCount
    );

}

void BatchRenderer::SetShader(ShaderProgram &program)
{

    data.shader = program;
    data.shader.Bind();

}

void BatchRenderer::DrawQuad(
    const Vector2 &position, const Vector2 &scale,
    const Vector4 &color
)
{

    data.vertexIndex = CreateQuadInArray(
        data.vertices,
        data.vertexIndex,
        position, scale, color
    );
    
    data.indexCount += 6;

}

void BatchRenderer::DrawQuad(
    const Vector2 &position, const Vector2 &scale,
    const Texture &texture, const Vector4 &color
)
{

    int textureIndex;

    if (
        data.textureSlotLookup.find(texture.GetID())
        == data.textureSlotLookup.end()
    )
    {

        if (data.currentTextureSlot >= data.maxTextures)
        {
            EndBatch();
            SendBatch();
            BeginBatch();
        }

        texture.Bind(data.currentTextureSlot);
        data.textureSlotLookup[texture.GetID()]
            = data.currentTextureSlot;
        textureIndex = data.currentTextureSlot;

        data.currentTextureSlot++;

    }
    else
    {

        textureIndex = data.textureSlotLookup[
            texture.GetID()
        ];

    }

    data.vertexIndex = CreateQuadInArray(
        data.vertices,
        data.vertexIndex,
        position, scale, color, textureIndex
    );

    data.indexCount += 6;

}