
#version 330 core
/*
 *  Simple vertex shader for example four
 */

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTex;
out vec2 TexCoord;
out vec3 vertPos;
out vec3 normal;
out vec3 fragPos;
uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 normMat;
void main() {
	TexCoord = vec2(vTex.x, vTex.y);
	normal = mat3(normMat) * vNormal;
	fragPos = vec3(model * vec4(vPosition, 1.0f));
	gl_Position =  projection * view * model * vec4(vPosition, 1.0f);

}