#include "Core/game_handler.h"
#include "Camera/camera.h"

namespace gameHandler {

Game g_game;

bool Game::Init(){
    _playerCamera.Init(glm::vec3(0, 0, 3.0f));
    return true;
}

// TODO: the WASD movement should pass through a Player object
// which could hold a reference to the current camera
void MoveCamera(view::CAMERA_MOVEMENT value, float delta_time){
    g_game._playerCamera.MoveCamera(value, delta_time);
}

void updateCamera(float xOffset, float yOffset){
    g_game._playerCamera.ProcessMouseMovement(xOffset, yOffset);
}

void updateCameraZoom(float zOffset){
    g_game._playerCamera.ProcessMouseScroll(zOffset);
}

bool Init(){
    if(!g_game.Init())
        return false;
    return true;
}

void updateScreenSize(uint width, uint height){
    g_game._playerCamera._screenAspect = (float)width/(float)height;
}

glm::mat4 getViewMatrix(){
    return g_game._playerCamera.CalculateViewMatrix();
}

glm::mat4 getProjectionMatrix(){
    return g_game._playerCamera.CalculateProjectionMatrix();
}

glm::vec3 GetCameraPosition(){
    return g_game._playerCamera._position;
}

} // gameHandler