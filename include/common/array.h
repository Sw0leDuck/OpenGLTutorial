#ifndef ARRAY_H
#define ARRAY_H

#include "types.h"

namespace tartarus {

    // Currently has vector like behavior, will be refactor to
    // not need reallocations
    template<typename T, uint N = 5>
    struct Container {
        Container() {};
        ~Container() {
            for(uint i=0; i<_capacity; i++){
                free(_obj);
                _obj++;
            }
        };


        T* _obj;
        uint _size;
        uint _capacity;
    };

} // namespace tartarus


#endif