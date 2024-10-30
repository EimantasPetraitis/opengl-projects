#pragma once

#include <string>
#include <GL/glew.h>
#include <stb_image.h>

class Texture
{

private:

    unsigned int id;
    std::string filePath;
    unsigned char* localBuffer;
    int width, height, bytesPerPixel;

public:

    Texture(const std::string& path);
    Texture();
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return width; }
    inline int GetHeight() const { return height; }
    inline unsigned int GetID() const { return id; }

};