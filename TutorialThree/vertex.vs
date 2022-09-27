
#version 330 core
/*
 *  Simple vertex shader for example four
 */

in vec3 vPosition;
out vec3 vertPos;
void main() {
	
	gl_Position =  vec4(vPosition, 1.0f);

}