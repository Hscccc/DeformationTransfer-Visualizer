#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;
    GLuint getProgram() const;

private:
    GLuint program;

    std::string readFile(const std::string& path);
    GLuint compileShader(const std::string& source, GLenum type);
};

#endif
