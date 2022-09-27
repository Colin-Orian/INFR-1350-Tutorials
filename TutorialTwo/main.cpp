#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
//Screen Dimensions Variables
const unsigned int screen_width = 1024;
const unsigned int screen_height = 768;
//Number of Vertices
const GLuint NumVertices = 6;


const char* vertexShaderSource = "#version 330 core\n \
layout (location = 0) in vec3 aPos;\n \
out vec3 vertPos;\n \
void main()\n \
{\n \
   vertPos = vec3(aPos.x, aPos.y, aPos.z);\n\
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n \
}";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertPos; \n"
"void main()\n"
"{\n"
"   vec3 ourColor = vertPos;"  
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

int shaderProgram;

GLuint VBO;
GLuint VAO;
void processInput(GLFWwindow* window);

void initMesh(); 
void initShader();
void render();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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


    initMesh();
    initShader();
    //This loop renders the window we created above
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        render();
        //Swap buffers
        glfwSwapBuffers(window);
        //Poll for Input/Output Events such a key pressed, mouse clicked etc...
        glfwPollEvents();
    }
    //Terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}
//If a relevant key (e.g. Escape) is pressed then execute the code in the body. Herein close the window.
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void render() {
    
    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

void initMesh(void)
{

    float vertices[] = {
    -1.0f, -1.0f, 0.0f, // left corner
    1.0f, -1.0f, 0.0f,// right corner
    0.0f,  0.0f, 0.0f,// top corner
    -1.0f, 1.0f, 0.0f,// left corner
    1.0f, 1.0f, 0.0f, //right corner
    0.0f, 0.0f, 0.0f//top corner
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void initShader()
{
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}