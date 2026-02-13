#version 460 core
layout ( location = 0 ) in vec3 aPos;
layout ( location = 1 ) in vec3 aNormal;
layout ( location = 2 ) in vec2 aTexCoords; 
layout ( location = 3 ) in vec3 aOffsets;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelInverseTransposeMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main(){
    FragPos = vec3(modelMatrix * vec4(aPos + aOffsets, 1.0));
    Normal = mat3(modelInverseTransposeMatrix) * aNormal;
    TexCoords = aTexCoords;
    gl_Position = projectionMatrix * viewMatrix * vec4(FragPos, 1.0);
    // gl_Position = modelMatrix * vec4(aPos, 1.0);
}