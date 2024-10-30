#pragma once

#include <vector>
#include <stdexcept>

#include <GL/glew.h>

struct VertexBufferLayoutElement
{

    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int GetTypeSize(unsigned int type)
    {

        switch (type)
        {
            case GL_BYTE : return sizeof(char);
            case GL_UNSIGNED_BYTE : return sizeof(unsigned char);
            case GL_SHORT : return sizeof(short);
            case GL_UNSIGNED_SHORT : return sizeof(unsigned short);
            case GL_INT : return sizeof(int);
            case GL_UNSIGNED_INT : return sizeof(unsigned int);
            case GL_FLOAT : return sizeof(float);
            case GL_DOUBLE : return sizeof(double);
        }

        std::runtime_error(nullptr);
        return 0;

    }

};

class VertexBufferLayout
{

private:

    std::vector<VertexBufferLayoutElement> elements;

    unsigned int stride;

public:

    VertexBufferLayout();

    void Push(unsigned int type, unsigned int count, bool normalized);

    inline const std::vector<VertexBufferLayoutElement> GetElements() const { return elements; };
    
    inline unsigned int GetStride() const { return stride; };

};