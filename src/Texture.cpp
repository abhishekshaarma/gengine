#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string &path)
    :rendererID_(0), filepath_(path), localbuffer_(nullptr), width_(0), height_(0), bpp_(0)
{
    stbi_set_flip_vertically_on_load(1);
    localbuffer_ = stbi_load(path.c_str(), &width_, &height_, &bpp_, 4);
    
    glGenTextures(1, &rendererID_);
    glBindTexture(GL_TEXTURE_2D, rendererID_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, localbuffer_);

    Unbind();
    
    if(localbuffer_)
    {
        stbi_image_free(localbuffer_);
    }
    if (!localbuffer_)
    {
        std::cout << "Failed to load texture: " << path << "\n";
        {
            std::cerr << "Failed to load: " << path << "\n";
            std::cerr << "stb reason: " << stbi_failure_reason() << "\n";
        }

    }

}

Texture::~Texture()
{
    glDeleteTextures(1, &rendererID_);
        
}

void Texture::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, rendererID_);
    
        
}
void Texture::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}


