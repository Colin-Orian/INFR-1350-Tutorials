#version 330 core;
in vec3 aPos;
void main(){
    int isBlue = 0;
    vec3 color;

    color = (1- isBlue)* vec3(0.0, 0.0, 1.0) +  isBlue * vec3(1.0, 0.0, 0.0);
    FragColor = color;


}