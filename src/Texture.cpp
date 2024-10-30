#include "Texture.h"

Texture::Texture(const std::string& path)
    : id(0), filePath(path), localBuffer(nullptr),
    width(0), height(0), bytesPerPixel(0)
{

    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(
        path.c_str(), &width, &height, &bytesPerPixel, 4
    );

    glGenTextures(1, &id);
    Bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, localBuffer
    );
    Unbind();

    if (localBuffer)
        stbi_image_free(localBuffer);

}

Texture::Texture()
    : id(0), filePath(""), localBuffer(nullptr),
    width(0), height(0), bytesPerPixel(0)
{}

Texture::~Texture()
{

    glDeleteTextures(1, &id);

}

void Texture::Bind(unsigned int slot /* = 0*/) const
{

    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);

}

void Texture::Unbind() const
{

    glBindTexture(GL_TEXTURE_2D, 0);

}