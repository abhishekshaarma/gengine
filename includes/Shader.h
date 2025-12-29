#pragma once
#include <string>
#include <unordered_map>
struct ShaderSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
  private:
    unsigned int rendererID_;
    std::string filepath_;
    std::unordered_map<std::string, int> locationCache_; 

  public:
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // uniforms
    void SetUniform4f(const std::string& name,
                      float v0, float v1, float v2, float v3);
    int GetUniformLocation(const std::string& name) ;

  private:
    ShaderSource ParseShader(const std::string& pathname);
    unsigned int CompileShader(unsigned int type,
                               const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader,
                              const std::string& fragmentShader);
};
