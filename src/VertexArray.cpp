#include "VertexArray.h"

#include "debug.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &rendererid_);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&rendererid_);
}
void VertexArray::addBuffer(const VertexBuffer& vb,
                            const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();

    const auto& elements = layout.getElements();
    size_t offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& e = elements[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            e.count,
            e.type,
            e.normalized,
            layout.getStride(),
            reinterpret_cast<const void*>(offset)
            );

        offset += e.count * VertexBufferElement::getSizeofType(e.type);
    }
}
void VertexArray::Bind() const
{
    glBindVertexArray(rendererid_);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}

