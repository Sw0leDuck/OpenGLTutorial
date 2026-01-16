#ifndef CAMERA_H
#define CAMERA_H

#include "glm/gtc/type_ptr.hpp"
#include "common/types.h"

namespace view {

#define YAW        -90.f
#define PITCH        0.f
#define ROLL         0.f
#define SPEED       2.5f
#define SENSITIVITY 0.1f 

    enum CAMERA_MOVEMENT : uint {
        kMoveForward = 0,
        kMoveBackward = 1,
        kMoveLeft = 2,
        kMoveRing = 3
    };

    struct Camera{

        void Init(
            glm::vec3 position = glm::vec3(0),
            float yaw = YAW,
            float pitch = PITCH,
            float roll = ROLL,
            float camera_speed = SPEED,
            float camera_sensitivity = SENSITIVITY);
        void Exit();
        void UpdateCamera(float xOffset, float yOffset);

        glm::vec3 _position;
        glm::vec3 _camera_target;
        glm::vec3 _camera_front;
        glm::vec3 _up_vector;

        float _camera_speed;
        
        // normalized
        glm::vec3 _camera_z_axis;
        glm::vec3 _camera_x_axis;
        glm::vec3 _camera_y_axis;

        glm::vec3 _direction;

        float _yaw;
        float _pitch;
        float _roll;

        float _camera_sensitivity;

        glm::mat4 LookAt();
        glm::mat4 CalculateViewMatrix();
    };
}

#endif