#include "Shader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include <GL/glew.h>

Shader::Shader(const std::string& filepath)
    :  rendererID_(0), filepath_(filepath)
{
    ShaderSource source = ParseShader(filepath_);
    rendererID_ = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
    glDeleteProgram(rendererID_);
}

void Shader::Bind() const
{
    glUseProgram(rendererID_);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name,
                          float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int Shader::GetUniformLocation(const std::string& name) 
{
    if(locationCache_.find(name) != locationCache_.end())
        return locationCache_[name];
    
    int location = glGetUniformLocation(rendererID_, name.c_str());
    if (location == -1)
        std::cout << "Warning: uniform '" << name << "' not found\n";
    
    locationCache_[name] = location;
    return location;
}

ShaderSource Shader::ParseShader(const std::string &pathname)
{
    std::ifstream stream(pathname);

    if (!stream)
        throw std::runtime_error("Failed to open shader file");


    enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)

        {
            if(line.find("vertex") != std::string::npos)
                //set vertex
            {
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
                    
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
            
    }
    
    

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);

    // returns a pointer to the begingi of the sring[] src = &source[0] basically
    const char* src = source.c_str(); 

    // if length is null each string is actually nullterminated 
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: ERROR HANDLING -> done to some extent 
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


unsigned int Shader::CreateShader(const std::string& vertexShader,const std::string& fragmentShader)
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

