#pragma once

#include <GL/glew.h>

unsigned int* CalculateQuadIndices(unsigned int indicesCount);

class IndexBuffer
{

private:

    unsigned int id;
    unsigned int size;
    unsigned int count;

public:

    IndexBuffer(const void* data, unsigned int size, unsigned int count);
    IndexBuffer();
    
    ~IndexBuffer();

    void Generate(const void* data, unsigned int size, unsigned int count);
    
    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return count; };

};