#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

namespace tartarus {

// primitive object 
struct GameObject {
    enum class Type{
        kCamera = 0,
        kStatic = 1,
        kLight = 2
    };


    virtual bool Init() { return false; }
    virtual bool Exit() { return false; }
    virtual void Draw(float) { }
    virtual void Update(float) { }


    Type _type;
};

}

#endif