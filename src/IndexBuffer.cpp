#include "IndexBuffer.h"
#include <GL/glew.h>
#include "debug.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    :count_(count)
{
    glGenBuffers(1, &rendererid_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererid_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

void IndexBuffer::Bind() const  
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererid_);
}

void IndexBuffer::Unbind() const 
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &rendererid_);
}


