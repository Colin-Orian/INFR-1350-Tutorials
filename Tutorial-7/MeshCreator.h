#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
struct MeshData {
    GLuint objVAO;
    GLuint posVBO;
    GLuint normalVBO;
    GLuint indexVBO;
    GLuint uvVBO;
    int numVertices;
    int triangles;
};
struct MeshData* createMesh(std::string fileName, int shaderProgram);

