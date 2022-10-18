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

//Screen Dimensions Variables
const unsigned int screen_width = 1024;
const unsigned int screen_height = 768;
//Number of Vertices
const GLuint NumVertices = 6;
int shaderProgram;

void processInput(GLFWwindow* window);
void render(struct MeshData* meshData);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void update();
void updateSecond();
bool isWireFrame = false;

glm::mat4 transform = glm::mat4(1);
glm::mat4 transformSecond = glm::mat4(1);

glm::mat4 projection = glm::mat4(1);
glm::mat4 view = glm::mat4(1);


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
    MeshData* meshData = createMesh("monkey.obj", shaderProgram);
    
    projection = glm::perspective(glm::radians(45.0f), (float)screen_width /
        (float)screen_height, 0.1f, 200.0f);
    //projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 200.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -250.0f));

    update();
    updateSecond();
    //This loop renders the window we created above
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
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
}

//Perform the desired transformations to our transformation matrix
void updateSecond() {
    
    transformSecond = glm::translate(transformSecond, glm::vec3(-0.5f, 0.0f, 100.0f));
    
    transformSecond = glm::rotate(transformSecond, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    
    transformSecond = glm::scale(transformSecond, glm::vec3(1.0f, 1.0f, 1.0f));

}


void update() {

    transform = glm::translate(transform, glm::vec3(0.5f, 0.0f, 100.0f));

    transform = glm::rotate(transform, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));

    transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));

}
void render(struct MeshData* meshData) {

    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);


    loadUniformMat4x4(shaderProgram, "model", transform);
    loadUniformMat4x4(shaderProgram, "projection", projection);
    loadUniformMat4x4(shaderProgram, "view", view);
    glBindVertexArray(meshData->objVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 3 * meshData->triangles, GL_UNSIGNED_SHORT, NULL);

    loadUniformMat4x4(shaderProgram, "model", transformSecond);
    glDrawElements(GL_TRIANGLES, 3 * meshData->triangles, GL_UNSIGNED_SHORT, NULL);
    

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}