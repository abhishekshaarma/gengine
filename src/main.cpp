#include <cmath>
#include <iostream>
#include <vector>

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

static unsigned int CompileShader(unsigned int type, const std::string source)
{
    unsigned int id = glCreateShader(type);
    // returns a pointer ti the begingi of the sring[] src = &source[0] basically
    const char* src = source.c_str(); 
    // if length is null each string is actually nullterminated 
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    //TODO: ERROR HANDLING 
    int result;
    // Query to see the shader file i -> interger v -> vector
    glGetShaderiv(id , GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        //
        char *message = (char*)alloca(length * sizeof(char)); // allocates on the stack dynamically(whoa!)
        glGetShaderInfoLog(id,length, &length, message);
        std::cout << "Failed to compile shader -> " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragmenet" ) << message << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram(); // returns an unsigned int 
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

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
    float position[9] =
        {
            0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 2.0f,
            0.0f, 1.0f, 1.0f
        };
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);
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

    glEnableClientState(GL_VERTEX_ARRAY);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 2, GL_FLOAT, 0, sizeof(float) * 2, (const void*)0);

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "\n"
        "gl_Position = position;\n"
        
        "}\n";


    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout (location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "\n"
        "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        
        "}\n";
    
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);


    
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
