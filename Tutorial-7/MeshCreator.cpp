#include "MeshCreator.h"
#include "tiny_obj_loader.h"

MeshData* createMesh(std::string fileName, int shaderProgram)
{
    MeshData* meshData = new MeshData();
    tinyobj::attrib_t inattrib;
    std::string warn;
    std::string err;
    //Contains all the shapes we have in our OBJ file. Since we'll have 1 shape, this vector will have a length of 1
    std::vector<tinyobj::shape_t> shapes;
    //We won't be using the materials but the LoadObj() function requires it to work
    std::vector<tinyobj::material_t> materials;

    /*
    std::string err = tinyobj::LoadObj(shapes, materials, fileName.c_str(), 0);
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }*/
    std::string baseDir = ".";

    bool ret = tinyobj::LoadObj(&inattrib, &shapes, &materials, &warn, &err, fileName.c_str(),
        baseDir.c_str());

    if (!warn.empty()) {
        std::cout << "WARN: " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << err << std::endl;
    }
    if (!ret) {
        std::cerr << "Failed to load " << fileName << std::endl;

    }
    //We need to know how much data is in the mesh
    int nv = (int)(inattrib.vertices.size());

    GLfloat* vertices = new GLfloat[nv];
    //Go through each of the mesh's positions and store it into our vertices array
    for (int i = 0; i < nv; i++) {
        vertices[i] =  inattrib.vertices[i];
        
    }

 
    //Retrieve the meshes normals
    int nn = (int)(inattrib.normals.size());
    GLfloat* normals = new GLfloat[nn];
    for (int i = 0; i < nn; i++) {
        normals[i] = inattrib.normals[i];

    }
    

    /*  Retrieve the triangle indices */

    int ni = shapes[0].mesh.indices.size();
    
    meshData->triangles = ni;
    
    GLuint* indices = new GLuint[ni];
    for (int i = 0; i < ni; i++) {
        indices[i] = shapes[0].mesh.indices[i].vertex_index;
    }

    
    //Retrive the triangle's UV coords
    int nt = inattrib.texcoords.size();
    GLfloat* uvCoords = new GLfloat[nt];
    for (int i = 0; i < nt; i++) {
        uvCoords[i] = inattrib.texcoords[i];
    }


    meshData->numVertices = nv;
    std::cout << "Number Triangles " << meshData->triangles << std::endl;
    std::cout << "Number Vertices: " << nv << std::endl;
    std::cout << "Number Normals: " << nn << std::endl;
    std::cout << "Number Indicies: " << ni << std::endl;
    std::cout << "Number UVs" << nt << std::endl;
    //std::cout << "test" << std::endl;

    glGenVertexArrays(1, &meshData->objVAO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(meshData->objVAO);


    

    // position attribute
    glGenBuffers(1, &meshData->posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshData->posVBO);
    glBufferData(GL_ARRAY_BUFFER, nv * sizeof(float), vertices, GL_STATIC_DRAW);

    
    //Normal Attributes
    glGenBuffers(1, &meshData->normalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, meshData->normalVBO);
    glBufferData(GL_ARRAY_BUFFER, nn * sizeof(float), normals, GL_STATIC_DRAW);

    //index attribute
    glGenBuffers(1, &meshData->indexVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->indexVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ni * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glGenBuffers(1, &meshData->uvVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData->uvVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nt * sizeof(float), uvCoords, GL_STATIC_DRAW);

    glUseProgram(shaderProgram);

    GLint vPosition = glGetAttribLocation(shaderProgram, "vPosition");
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vPosition);

    GLint vNormal = glGetAttribLocation(shaderProgram, "vNormal");
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vNormal);

    GLint vTexCoord = glGetAttribLocation(shaderProgram, "vTex");
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vTexCoord);
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    delete[] vertices;
    delete[] normals;
    delete[] uvCoords;
    delete[] indices;
    return meshData;
}
