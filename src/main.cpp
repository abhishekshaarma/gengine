#include <cmath>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

#include "gl3d.h"
#include "View.h"
#include "SingletonView.h"
#include "Reshape.h"
#include "Material.h"
#include "Light.h"

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
    float vertices[9] =
        {
            0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 2.0f,
            0.0f, 1.0f, 1.0f
        };
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    mygllib::SingletonView::getInstance()->lookat();

    mygllib::draw_axes();

    glPushMatrix();
    glTranslatef(-2.5f, 0.0f, -1.5f);

    glEnableClientState(GL_VERTEX_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 2, GL_FLOAT, 0, sizeof(float) * 2, (const void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);

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
