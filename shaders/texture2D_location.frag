#version 460 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 texCoords;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;
uniform float mix_percentage;

void main() {
    FragColor = mix(texture(ourTexture0, texCoords), texture(ourTexture1, texCoords), mix_percentage);
}