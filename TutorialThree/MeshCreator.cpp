#include "MeshCreator.h"
#include "tiny_obj_loader.h"

MeshData* createMesh(std::string fileName, int shaderProgram)
{
    MeshData* meshData = new MeshData();
    //Contains all the shapes we have in our OBJ file. Since we'll have 1 shape, this vector will have a length of 1
    std::vector<tinyobj::shape_t> shapes;
    //We won't be using the materials but the LoadObj() function requires it to work
    std::vector<tinyobj::material_t> materials;

    std::string err = tinyobj::LoadObj(shapes, materials, fileName.c_str(), 0);
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    //We need to know how much data is in the mesh
    int nv = shapes[0].mesh.positions.size();
    GLfloat* vertices = new GLfloat[nv];
    //Go through each of the mesh's positions and store it into our vertices array
    for (int i = 0; i < nv; i++) {
        vertices[i] = shapes[0].mesh.positions[i];
    }


    /*  Retrieve the triangle indices */

    int ni = shapes[0].mesh.indices.size();
    meshData->triangles = ni / 3;
    GLushort* indices = new GLushort[ni];
    for (int i = 0; i < ni; i++) {
        indices[i] = shapes[0].mesh.indices[i];
    }

    meshData->numVertices = nv / 3;

    glGenVertexArrays(1, &meshData->objVAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(meshData->objVAO);

    // position attribute
    glGenBuffers(1, &meshData->posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshData->posVBO);
    glBufferData(GL_ARRAY_BUFFER, nv * sizeof(float), vertices, GL_STATIC_DRAW);

    //index attribute
    glGenBuffers(1, &meshData->indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ni * sizeof(GLushort), indices, GL_STATIC_DRAW);



    glUseProgram(shaderProgram);

    GLint vPosition = glGetAttribLocation(shaderProgram, "vPosition");
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);



    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    delete[] vertices;
    delete[] indices;
    return meshData;
}
