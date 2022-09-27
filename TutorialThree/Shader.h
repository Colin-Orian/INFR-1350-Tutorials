#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

std::string readFile(std::string fileName);

int createVertexShader(std::string shaderCode);

int createFragmentShader(std::string shaderCode);

GLuint createShaderProgram(std::string vertexFile, std::string fragFile);
