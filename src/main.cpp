#include <GL/glew.h>
#include <GL/freeglut.h>
#include <memory>

#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Reshape.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "ImageFile.h"
#include "Texture.h"


unsigned int indices[] =
{
    0, 1, 2,
    3, 2, 0
};
float position[] = {
    // x     y     z     u     v
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
    0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f
};
float r = 0.0f;
float increment = 0.05f;

// --------------------------------------------------
// GL objects (created AFTER context)
// --------------------------------------------------
std::unique_ptr<Renderer> renderer;
std::unique_ptr<VertexArray> va;
std::unique_ptr<VertexBuffer> vb;
std::unique_ptr<IndexBuffer> ib;
std::unique_ptr<Shader> shader;
std::unique_ptr<Texture> texture;
VertexBufferLayout layout;

// --------------------------------------------------
void init()
{
    auto& view = *mygllib::SingletonView::getInstance();
    view.eyex() = 6.0f;
    view.eyey() = 5.0f;
    view.eyez() = 10.0f;
    view.lookat();
    
    
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    //enbable for blending the texture
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    renderer = std::make_unique<Renderer>();

    va = std::make_unique<VertexArray>();

    //vb = std::make_unique<VertexBuffer>(position, 4 * 5 * sizeof(float));
    vb = std::make_unique<VertexBuffer>(position, sizeof(position));
    layout.Push<float>(3);
    layout.Push<float>(2);
    va->addBuffer(*vb, layout);

    ib = std::make_unique<IndexBuffer>(indices, 6);

    shader = std::make_unique<Shader>("shader/Basic.shader");
    shader->Bind();
    shader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

    glActiveTexture(GL_TEXTURE0);
    shader->SetUniform1i("u_Texture", 0);

    texture = std::make_unique<Texture>("images/light.png");
}

// --------------------------------------------------
void display()
{
    renderer->Clear();

    shader->Bind();
    texture->Bind(0);
   


    renderer->draw(*va, *ib, *shader);

    glutSwapBuffers();
    glutPostRedisplay();
}

// --------------------------------------------------
void keyboard(unsigned char key, int, int)
{
    if (key == 27) // ESC
        glutLeaveMainLoop();
}

// --------------------------------------------------
int main(int argc, char** argv)
{
    mygllib::init3d();   // creates window + GL context
    glewInit();          // MUST be after context

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
