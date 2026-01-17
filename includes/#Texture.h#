#pragma once
#include "Renderer.h"

class Texture
{
  private:
    unsigned int rendererID_;
    std::string filepath_;
    unsigned char* localbuffer_;
    int width_;
    int height_;
    int bpp_;

  public:
    Texture(const std::string &path);
    
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int getWidth() const {return width_;}
    inline  int getHeight() const {return height_;}
};
