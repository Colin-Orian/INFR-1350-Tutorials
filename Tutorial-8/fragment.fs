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
   vec3 lightPos = vec3(0.0f, 6.0f, 125.0f);
   vec3 objectColour = texture(texture1, TexCoord).xyz;
   vec3 lightColour = vec3(1.0f, 1.0f, 1.0f);

   float ambientStrength = 0.3f;
   vec3 ambientLight = ambientStrength * lightColour;   
   
   vec3 norm = normalize(normal);
   vec3 lightDir = normalize(lightPos - fragPos);
   float angleIncident = max(dot(lightDir, norm), 0.0f);
   vec3 diffuseLight = angleIncident * lightColour;

   float specularStrength = 1.0;

   vec3 viewDir = (eyePos - fragPos);
   viewDir = normalize(viewDir);
   vec3 reflectDir = reflect(-lightDir, norm);
   reflectDir = normalize(reflectDir);

   float shininess = 32.0f;
   float specular = pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
   vec3 specularLight = specularStrength * specular * lightColour;

   vec3 totalLight = (ambientLight + diffuseLight + specularLight) * objectColour;
   FragColor = vec4(totalLight, 1.0f);

   
}