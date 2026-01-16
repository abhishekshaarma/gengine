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

GLuint texWall  = 0;

static inline void loadTexture(GLuint& texID, const std::string& filename)
{
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);

    BMPFile bmp(filename);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 bmp.width(), bmp.height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, bmp.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


unsigned int indices[] =
{
    0, 1, 2,
    3, 2, 0
};

float position[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
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

VertexBufferLayout layout;

// --------------------------------------------------
void init()
{
    auto& view = *mygllib::SingletonView::getInstance();
    view.eyex() = 6.0f;
    view.eyey() = 5.0f;
    view.eyez() = 10.0f;
    view.lookat();
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
 
    
    
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);

    loadTexture(texWall,  "images/wood.bmp");
    

    renderer = std::make_unique<Renderer>();

    va = std::make_unique<VertexArray>();

    vb = std::make_unique<VertexBuffer>(position, 4 * 3 * sizeof(float));
    layout.Push<float>(3);
    va->addBuffer(*vb, layout);

    ib = std::make_unique<IndexBuffer>(indices, 6);

    shader = std::make_unique<Shader>("shader/Basic.shader");
    shader->Bind();
}

// --------------------------------------------------
void display()
{
    glBindTexture(GL_TEXTURE_2D, texWall);

    renderer->Clear();

    shader->Bind();
    shader->SetUniform4f("u_Color", r, 0.3f, 0.8f, 0.2f);

    if (r > 1.0f) increment = -0.05f;
    else if (r < 0.0f) increment = 0.05f;
    r += increment;

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
