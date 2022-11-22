#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec3 vertPos;
in vec3 normal;
in vec3 fragPos;
in vec2 TexCoord;
// texture sampler
uniform sampler2D texture1;
uniform vec3 eyePos;

void main()
{

   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
   
}