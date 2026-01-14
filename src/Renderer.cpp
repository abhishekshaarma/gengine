#include "Renderer.h"


void Renderer::draw(VertexArray &vs, const IndexBuffer &ib, const Shader& shader) const
{
    
}

/*

inline void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mygllib::SingletonView::getInstance()->lookat();

    mygllib::draw_axes();

    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
    
    VertexArray va;
    VertexBuffer vb(position, 4*2 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);
    
    Shader shader("shader/Basic.shader");
    shader.Bind();
    shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
      
    
    DEBUG();
   
    va.Bind();
    ib.Bind();
    vb.Unbind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    shader.Unbind();
    DEBUG();
     glPopMatrix();
    glutSwapBuffers();
}

 */
