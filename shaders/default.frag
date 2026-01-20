#version 460 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess; 
};

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    float outerRing;
    float innerRing;
};

#define NR_POINT_LIGHTS 4

uniform Material material;
uniform DirLight dirLight;
uniform PointLight[NR_POINT_LIGHTS] pointLight;
uniform vec3 viewPos;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

vec3 CalcDirLight(vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = dirLight.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = dirLight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = dirLight.specular * spec * texture(material.specular, TexCoords).rgb;

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(int index, vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(pointLight[index].position - FragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(pointLight[index].position - FragPos);
    float attenuation = 1.0 / (pointLight[index].constant + pointLight[index].linear * distance + 
  			     pointLight[index].quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = pointLight[index].ambient  * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse  = pointLight[index].diffuse  * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = pointLight[index].specular * spec * texture(material.specular, TexCoords).rgb;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

void main(){
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = CalcDirLight(normal, viewDir);

    for(int i=0; i<NR_POINT_LIGHTS; i++)
        result += CalcPointLight(i, normal, viewDir);
    
    // calc spot light
    // result += CalcSpotLight();

    FragColor = vec4(result, 1.0);
}