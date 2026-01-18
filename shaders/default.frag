#version 460 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess; 
};

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

void main(){
    vec3 norm = normalize(Normal);

    // ambient calculation
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    // diffuse calculation
    vec3 lightDir = normalize(light.position - FragPos);
    float diffuseStrength = max(dot(norm, lightDir), 0);
    vec3 diffuse = light.diffuse * (diffuseStrength * vec3(texture(material.diffuse, TexCoords)));

    // specular
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec_value = pow(max(dot(viewDir, reflectDir),0), material.shininess);
    vec3 specular = light.specular * spec_value * vec3(texture(material.specular, TexCoords));

    vec3 emission = texture(material.emission, TexCoords).rgb;

    vec3 result = (specular + diffuse + ambient + emission);
    FragColor = vec4(result, 1.0f);
}