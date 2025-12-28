#pragma once


class IndexBuffer
{
  private:
    unsigned int rendererid_;
    unsigned int count_;

  public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind();
    void Unbind();
    inline unsigned int const getCount()
    {
        return count_;
    }
};
