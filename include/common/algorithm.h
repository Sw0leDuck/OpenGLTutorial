#ifndef ALGORITHM_H
#define ALGORITHM_H

namespace common {
    template<typename T>
    T min(const T& left, const T& right) {
        return left <= right ? left : right;
    }

    template<typename T>
    T max(const T& left, const T& right) {
        return left >= right ? left : right; 
    }

    template<typename T>
    T clamp(const T& value, const T& low, const T& high) {
        return max(min(value, high), low);
    }
}

#endif