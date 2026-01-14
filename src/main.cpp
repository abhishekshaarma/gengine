#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <string>
#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

unsigned int vao;


unsigned int indices[] =
{
    0 , 1, 2,
    3 , 2, 0
}; 
float position[18] =
{
    -0.5f,  -0.5f, 0.0f, //1
    0.5f, -0.5f, 0.0f,   // 2
    0.5f, 0.5f, 0.0f,    // 3
    -0.5f,  0.5f, 0.0f,  // 4
};


GLuint vbo = 0;


void init()
{
    auto& view = *mygllib::SingletonView::getInstance();
    view.eyex() = 6.0f;
    view.eyey() = 5.0f;
    view.eyez() = 10.0f;
    view.lookat();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    GLfloat sceneAmbient[] = {0.35f, 0.35f, 0.35f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, sceneAmbient);

    GLfloat lightPos[]      = {8, 10, 10, 1};
    GLfloat lightDiffuse[] = {1, 1, 1, 1};
    GLfloat lightSpecular[]= {1, 1, 1, 1};
    GLfloat lightAmbient[] = {0.4f, 0.4f, 0.4f, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glEnable(GL_LIGHT0);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glClearColor(0, 0, 0, 1);

    // -------------------------------
    // Create VBO ONCE
    // -------------------------------
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

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

void keyboard(unsigned char, int, int)
{
    glutPostRedisplay();
}

void special(int, int, int)
{
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    mygllib::init3d();   // creates GL context
    glewInit();          // MUST be after context
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(mygllib::Reshape::reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    glutMainLoop();
    return 0;
}

/*
  1. uniforms are set per draw,
  you can set a uniform up before the draw

  12. VertexArray
  
*/
