#include "ModelLoader.h"
#include <iostream>
#include <vector>
#include <GL/glew.h>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

typedef OpenMesh::TriMesh_ArrayKernelT<>  Mesh;

ModelLoader::ModelLoader() : VAO(0), VBO(0), EBO(0), indexCount(0) {}

ModelLoader::~ModelLoader() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void ModelLoader::loadModel(const std::string& path) {
    Mesh mesh;
    if (!OpenMesh::IO::read_mesh(mesh, path)) {
        std::cerr << "Error: Cannot read mesh from " << path << std::endl;
        return;
    }

    mesh.request_face_normals();
    mesh.request_vertex_normals();
    mesh.update_normals();

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (const auto& vertex : mesh.vertices()) {
        auto point = mesh.point(vertex);
        auto normal = mesh.normal(vertex);

        vertices.push_back(point[0]);
        vertices.push_back(point[1]);
        vertices.push_back(point[2]);

        vertices.push_back(normal[0]);
        vertices.push_back(normal[1]);
        vertices.push_back(normal[2]);
    }

    for (const auto& face : mesh.faces()) {
        for (const auto& vertex : mesh.fv_range(face)) {
            indices.push_back(vertex.idx());
        }
    }

    indexCount = indices.size();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL Error: " << error << std::endl;
    }
}

void ModelLoader::render() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}