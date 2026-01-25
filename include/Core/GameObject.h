#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

namespace tartarus {

// primitive object 
struct GameObject {
    virtual bool Init();
    virtual bool Exit();

    enum class Type{
        kCamera = 0,
        kCube = 1
    };

    Type _type;
};

}

#endif