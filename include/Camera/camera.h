#ifndef CAMERA_H
#define CAMERA_H
#include "glm/gtc/type_ptr.hpp"
#include "CameraTypes.h"
#include "Core/Objects/GameObject.h"

namespace tartarus {

#define YAW        -90.f
#define PITCH        0.f
#define ROLL         0.f
#define SPEED       2.5f
#define SENSITIVITY 0.1f
#define FOV         45.f

// FPSCamera, FLYCamera seems reductant: TODO: remove them
struct Camera : GameObject {
    bool Init() override;
    bool Exit() override;
    void Update(float) override;
    
    void Init(glm::vec3 position = glm::vec3(0),
        float yaw = YAW,
        float pitch = PITCH,
        float roll = ROLL,
        float camera_speed = SPEED,
        float camera_sensitivity = SENSITIVITY,
        float camera_fov = FOV);
    
    glm::mat4 LookAt();
    glm::mat4 CalculateViewMatrix();
    glm::mat4 CalculateProjectionMatrix();

    glm::vec3 _position;
    glm::vec3 _cameraTarget;
    glm::vec3 _cameraFront;
    glm::vec3 _upVector;
    float _cameraSpeed;
    float _cameraSensitivity;
    float _fov;
    float _screenAspect;
    float _near;
    float _far;
    
    // normalized
    glm::vec3 _cameraZAxis;
    glm::vec3 _cameraXAxis;
    glm::vec3 _cameraYAxis;
    glm::vec3 _direction;
    float _yaw;
    float _pitch;
    float _roll;

    OffsetCoordinates _offsets;
    CAMERA_MOVEMENT _movement;
};
}

#endif