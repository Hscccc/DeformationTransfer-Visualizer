#ifndef MODELLOADER_H
#define MODELLOADER_H

#include <string>
#include <GL/glew.h>

class ModelLoader {
public:
    ModelLoader();
    ~ModelLoader();

    void loadModel(const std::string& path);
    void render();

private:
    GLuint VAO, VBO, EBO;
    unsigned int indexCount;
};

#endif
