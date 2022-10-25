#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 vertPos;
void main()
{
   vec3 ourColor = vertPos;
   FragColor = vec4(ourColor, 1.0f);
}