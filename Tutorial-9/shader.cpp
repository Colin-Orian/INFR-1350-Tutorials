#include "Shader.h"
std::string readFile(std::string fileName)
{
	std::ifstream file;
	std::string fileLine;
	std::string fileContents;
	try {

		file.open(fileName);

		while (std::getline(file, fileLine)) {
			fileContents += fileLine;
			fileContents += '\n';
		}
	}
	catch (std::ifstream::failure& e) {
		std::cout << "Error opening / reading file: " << std::endl;
	}

	file.close();
	return fileContents;
}



GLuint createShaderProgram(std::string vertexFile, std::string fragFile)
{
	std::string vertexContent = readFile(vertexFile);
	std::string fragContent = readFile(fragFile);
	int vertexShader = createVertexShader(vertexContent);
	int fragmentShader = createFragmentShader(fragContent);

	// link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

//Create a Uniform variable that is a 4 by 4 matrix for the shader program. The uniform varaible will have the
//uniformName
void loadUniformMat4x4(GLuint shaderProgam, std::string uniformName, glm::mat4 data)
{
	int varLoc = glGetUniformLocation(shaderProgam, uniformName.c_str());
	glUniformMatrix4fv(varLoc, 1, 0, glm::value_ptr(data));
}

void loadUniformVec3(GLuint shaderProgram, std::string uniformName, glm::vec3 data) {
	int varLoc = glGetUniformLocation(shaderProgram, uniformName.c_str());
	glUniform3f(varLoc, data.x, data.y, data.z);
}

void loadUniformInt1(GLuint shaderProgram, std::string uniformName, int data)
{
	int varLoc = glGetUniformLocation(shaderProgram, uniformName.c_str());
	glUniform1i(varLoc, data);
}


int createFragmentShader(std::string shaderCode)
{

	const GLchar* shaderChars = shaderCode.c_str();
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderChars, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return fragmentShader;
}


int createVertexShader(std::string shaderCode) {
	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	const GLchar* shaderChars = shaderCode.c_str();
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderChars, NULL);
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

	return vertexShader;
}