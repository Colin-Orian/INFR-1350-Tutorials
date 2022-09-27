#include "MeshCreator.h"
#include "tiny_obj_loader.h"


struct MeshData* createMesh()
{
    MeshData* meshData = new MeshData();
    float vertices[] = {
    -1.0f, -1.0f, 0.0f, // left corner
    1.0f, -1.0f, 0.0f,// right corner
    0.0f,  0.0f, 0.0f,// top corner
    -1.0f, 1.0f, 0.0f,// left corner
    1.0f, 1.0f, 0.0f, //right corner
    0.0f, 0.0f, 0.0f//top corner
    };
    int arraySize = sizeof(vertices) / sizeof(vertices[0]);

    meshData->numVertices = arraySize / 3;

    glGenVertexArrays(1, &meshData->objVAO);
    glGenBuffers(1, &meshData->posVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(meshData->objVAO);
    glBindBuffer(GL_ARRAY_BUFFER, meshData->posVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    return meshData;
}