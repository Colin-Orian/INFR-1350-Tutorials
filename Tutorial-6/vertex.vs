
#version 330 core
/*
 *  Simple vertex shader for example four
 */

in vec3 vPosition;
in vec3 vNormal;
out vec3 vertPos;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
void main() {
	vertPos = normalize(vNormal);
	gl_Position =  projection * view * model * vec4(vPosition, 1.0f);

}