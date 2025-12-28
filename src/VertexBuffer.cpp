#include "VertexBuffer.h"
#include <GL/glew.h>



/*
  These are just buffer with actual data so just bytes.
  Vertex Arrays are needed to tie the buffer with actual layout
  Vertex Array Object is opengl way of storing that state
*/

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &rendererid_);
    glBindBuffer(GL_ARRAY_BUFFER, rendererid_);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Bind () const
{
    glBindBuffer(GL_ARRAY_BUFFER, rendererid_);
}

void VertexBuffer::Unbind() const 
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &rendererid_);
}
