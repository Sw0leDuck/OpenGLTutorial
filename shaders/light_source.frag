#version 460 core
out vec4 FragColor;

uniform vec3 lightColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

void main(){
    FragColor = vec4(lightColor, 1.0); // set all 4 vector values to 1.0
}