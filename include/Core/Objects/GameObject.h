#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "Common/Matrix.h"

namespace tartarus {

class Camera;

// primitive object 
struct GameObject {
    enum class Type{
        kCamera = 0,
        kStatic = 1,
        kLight = 2
    };

    template<class T>
    T* AsType() { return dynamic_cast<T*>(this); }

    virtual bool Init() { return false; }
    virtual bool Exit() { return false; }
    
    void SetWorldPosition(Matrix);
    void RotateWorldPosition(float degree, glm::vec3 vec3);
    void ScaleWorldPosition(glm::vec3 vec3);

    virtual void Draw(float) { }
    virtual void Update(float) { }


    Type _type;
    Matrix _worldPosition;
    Matrix _inverseModel;
    // The following 2 can even be pointer to the camera _view, _proj matrix
    // if we have many objects, we can not waste time on each frame setting the 
    // values
    Matrix _viewMatrix;
    Matrix _projectionMatrix;
};

}

#endif