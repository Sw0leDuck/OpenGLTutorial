namespace tartarus {

void Mesh3D::Init(){
    _modelMatrice._matrix = glm::mat4(1.0f);
    _viewMatrice._matrix = glm::mat4(1.0f);
    _projectionMatrice._matrix = glm::mat4(1.0f);

    _material._ambient = glm::vec3(0.2125	, 0.1275,	0.054);
    _material._diffuse = glm::vec3(0.714, 0.4284, 0.18144);
    _material._specular = glm::vec3(0.5f, 0.5f, 0.5f);
    _material._shininess = 32.0f;

    _light._ambient = glm::vec3( 0.1f, 0.1f, 0.1f);
    _light._diffuse = glm::vec3( 0.8f, 0.8f, 0.8f); // darken diffuse light a bit
    _light._specular = glm::vec3(1.0f, 1.0f, 1.0f);

    _objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
}

void Mesh3D::LoadDefaultUniforms(){
    LoadMatrixUniforms();
    // _program->SetFloat3("viewPos", _cameraPosition);
    
    // _program->SetFloat3("material.ambient", _material._ambient);
    // _program->SetInt("material.diffuse", 0);
    // _program->SetInt("material.specular", 1);
    // _program->SetInt("material.emission", 2);
    // _program->SetFloat("material.shininess", _material._shininess);
    
    // direction light
    // _program->SetFloat3("dirLight.direction", _light._lightDirection);
    // _program->SetFloat3("dirLight.ambient", _light._ambient);
    // _program->SetFloat3("dirLight.diffuse", _light._diffuse);
    // _program->SetFloat3("dirLight.specular", _light._specular);

    // Point Light ( 4 ) - TODO: REFACTOR THIS SHIT
    // _program->SetFloat3("pointLight[0].position", _pointLightPositions[0]);
    // _program->SetFloat3("pointLight[0].ambient", 0.05f, 0.05f, 0.05f);
    // _program->SetFloat3("pointLight[0].diffuse", 0.8f, 0.8f, 0.8f);
    // _program->SetFloat3("pointLight[0].specular", 1.0f, 1.0f, 1.0f);
    // _program->SetFloat("pointLight[0].constant", 1.0f);
    // _program->SetFloat("pointLight[0].linear", 0.09f);
    // _program->SetFloat("pointLight[0].quadratic", 0.032f);
        // point light 2
    // _program->SetFloat3("pointLight[1].position", _pointLightPositions[1]);
    // _program->SetFloat3("pointLight[1].ambient", 0.05f, 0.05f, 0.05f);
    // _program->SetFloat3("pointLight[1].diffuse", 0.8f, 0.8f, 0.8f);
    // _program->SetFloat3("pointLight[1].specular", 1.0f, 1.0f, 1.0f);
    // _program->SetFloat("pointLight[1].constant", 1.0f);
    // _program->SetFloat("pointLight[1].linear", 0.09f);
    // _program->SetFloat("pointLight[1].quadratic", 0.032f);


    // _program->SetFloat("light.cuttOf", glm::cos(glm::radians(12.5f)));
    // _program->SetFloat("light.outerCuttOf", glm::cos(glm::radians(17.5f)));
}
} // namespace graphic