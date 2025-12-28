#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
  private:
    unsigned int rendererid_;


  public:
    VertexArray();
    ~VertexArray();


    void addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
    
       
    void Bind() const;
    void UnBind() const;

        
    
};
