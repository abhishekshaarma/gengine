#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>



class OpenGLError
{};
inline void debug(const char * filename, int line_no)
{
    GLenum err;
    bool halt = false;
    while ((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << '\n' << filename << ':' << line_no << ": "
                  << "OpenGL error #" << err << ": "
                  << '[' << gluErrorString(err) << ']' << std::endl;
        halt = true;
    }
    if (halt) throw OpenGLError();
}

inline void DEBUG()
{
    debug(__FILE__, __LINE__);
}


#endif
