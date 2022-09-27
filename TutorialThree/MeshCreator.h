#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
struct MeshData {
    GLuint objVAO;
    GLuint posVBO;
    GLuint indexVBO;
    int numVertices;
    int triangles;
};
struct MeshData* createMesh();

