#ifndef GAME_HANDLER_H
#define GAME_HANDLER_H

#include "Camera/fps_camera.h"
#include "Camera/fly_camera.h"

namespace gameHandler {

    bool Init();

    void MoveCamera(view::CAMERA_MOVEMENT value, float delta_time);
    void updateCamera(float xOffset, float yOffset);
    void updateCameraZoom(float zOffset);
    void updateScreenSize(uint width, uint height);

    glm::vec3 GetCameraPosition();
    glm::vec3 GetCameraDirection();

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    struct Game {
        view::FlyCamera _playerCamera;
    
        bool Init();
    };

} // namespace gameHandler

#endif