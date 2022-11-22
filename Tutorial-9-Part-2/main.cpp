#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "MeshCreator.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//Screen Dimensions Variables
const unsigned int screen_width = 1024;
const unsigned int screen_height = 768;
//Number of Vertices
const GLuint NumVertices = 6;
int shaderProgram;


void processInput(GLFWwindow* window);
void render(struct MeshData* meshData);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


bool isWireFrame = false;

int main() {
    // Initialize GLFW and check if it works
    // ------------------------------
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initiate GLFW!\n");
        return -1;
    }

    // Set some Hints for the next glfwCreateWindow call.
    glfwWindowHint(GLFW_SAMPLES, 4); //Antializing set to x4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //Set the OpenGL version to 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4); //Set the OpenGL version to 4.x


    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //Set compatibility with newer versions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Set OpenGL core profile
    //Apple compatibility
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // Open a window and create its OpenGL context
    GLFWwindow* window;
    window = glfwCreateWindow(screen_width, screen_height, "SimpleWindowwithColor", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window); // Set the windows to render
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); //What happens when we change the window size
    // Load all OpenGL function pointers and check if GLAD works...
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    shaderProgram = createShaderProgram("vertex.vs", "fragment.fs");


    // Vertices
    float vertices[] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f
    };

    MeshData* meshData = new MeshData();
    glGenBuffers(1, &meshData->posVBO);
    glGenVertexArrays(1, &meshData->objVAO);
    glBindVertexArray(meshData->objVAO);
    glBindBuffer(GL_ARRAY_BUFFER, meshData->posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0); //Position data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    glBindVertexArray(0);
    //This loop renders the window we created above
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        render(meshData);
        //Swap buffers
        glfwSwapBuffers(window);
        //Poll for Input/Output Events such a key pressed, mouse clicked etc...
        glfwPollEvents();
    }
    //Terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    delete meshData;
    return 0;
}
//If a relevant key (e.g. Escape) is pressed then execute the code in the body. Herein close the window.
void processInput(GLFWwindow* window)
{

    
}

void render(struct MeshData* meshData) {

    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

    glBindVertexArray(meshData->objVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

    //glBindBuffer(GL_ARRAY_BUFFER, meshData->posVBO);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
