#ifndef BUFFER_H
#define BUFFER_H

namespace tartarus {

struct Buffer {
    virtual bool Init() { return false; };
    virtual bool Exit() { return false; };
    virtual bool IsValid() { return false; }

    enum Type {
        kInvalid = -1,
        kArray = 0,
        kElement = 1
    };

    Type _type = Type::kInvalid;
};

}

#endif