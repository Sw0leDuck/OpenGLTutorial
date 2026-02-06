// void UpdateMesh(glm::mat4 viewMatrix, glm::mat4 projectionMatrix, glm::vec3 cameraPosition, glm::vec3 cameraDirection){
//     [[__maybe_unused__]] static double hack_time = 0;
//     [[__maybe_unused__]] uint counter = 0;
//     hack_time += 0.005f;

//     glm::vec3 pointLightPositions[] = {
// 	    glm::vec3( 0.7f,  0.2f,  2.0f),
// 	    glm::vec3( 2.3f, -3.3f, -4.0f),
// 	    glm::vec3(-4.0f,  2.0f, -12.0f),
// 	    glm::vec3( 0.0f,  0.0f, -3.0f)
//     };

//     for(auto& iter : g_manager._meshManager._lightSources){
//         iter._modelMatrice.Translate(pointLightPositions[counter++]).
//                         Scale(glm::vec3(0.2f));
//         iter._viewMatrice._matrix = viewMatrix;
//         iter._projectionMatrice._matrix = projectionMatrix;
//     }
//     counter = 0;

//     for(auto& iter : g_manager._meshManager._meshes){
//         iter._modelInverseTransposeMatrice._matrix = glm::transpose(glm::inverse(iter._modelMatrice._matrix));
//         iter._viewMatrice._matrix = viewMatrix;
//         iter._projectionMatrice._matrix = projectionMatrix;
//         iter._cameraPosition = cameraPosition;
//         iter._light._lightDirection = cameraDirection;
//         iter._light._lightPosition = cameraPosition;
//         iter._pointLightPositions[0] = pointLightPositions[0];
//         iter._pointLightPositions[1] = pointLightPositions[1];
//         iter._pointLightPositions[2] = pointLightPositions[2];
//         iter._pointLightPositions[3] = pointLightPositions[3];
//     }
// }