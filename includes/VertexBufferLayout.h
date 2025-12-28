#pragma once

#include <vector>
#include <cassert>
#include <GL/glew.h>
#include "VertexBuffer.h"

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeofType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:         return sizeof(GLfloat);
            case GL_UNSIGNED_INT:  return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        assert(false && "Unknown GL type");
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> elements_;
    unsigned int stride_;

public:
    VertexBufferLayout()
        : stride_(0) {}

    template<typename T>
    void Push(unsigned int count);

    inline unsigned int getStride() const { return stride_; }
    inline const std::vector<VertexBufferElement>& getElements() const
    {
        return elements_;
    }
};

// =======================
//  Unsupported type
//   ======================= 
template<typename T>
void VertexBufferLayout::Push(unsigned int)
{
    static_assert(sizeof(T) == 0,
        "Unsupported type passed to VertexBufferLayout::Push");
}

// =======================
//float
// ======================= 

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    elements_.push_back({ GL_FLOAT, count, GL_FALSE });
    stride_ += count * VertexBufferElement::getSizeofType(GL_FLOAT);
}

// =======================
//   unsigned int
//   ======================= 
template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    elements_.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    stride_ +=  count * VertexBufferElement::getSizeofType(GL_UNSIGNED_INT);
}
template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    elements_.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    stride_ += count * VertexBufferElement::getSizeofType(GL_UNSIGNED_BYTE);
}
