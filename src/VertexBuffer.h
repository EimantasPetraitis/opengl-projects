#pragma once

#include <GL/glew.h>

class VertexBuffer
{

private:

    unsigned int id;
    bool dynamic;

public:

    VertexBuffer(unsigned int size, bool isDynamic = false);
    VertexBuffer(
        unsigned int size, const void* data, bool isDynamic = false
    );
    VertexBuffer();
    
    ~VertexBuffer();

    void Generate(unsigned int size, bool isDynamic = false);
    void Generate(
        unsigned int size, const void* data, bool isDynamic = false
    );
    
    void Bind() const;
    void Unbind() const;

    void SetData(int offset, int size, void* data);

};