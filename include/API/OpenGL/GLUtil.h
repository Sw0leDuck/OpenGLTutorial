#ifndef GL_UTIL_H
#define GL_UTIL_H
#include "Common/Logging.h"
#include "glad/glad.h"

namespace tartarus {

inline void CerberusCheck(const char* file, int line){
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        const char* error;
        switch (errorCode) {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default : error = "NO_VALID_CASE"; break;
        }
        LOG(ERROR, "%s in %s:%d", error, file, line);
    }
}

#ifdef NDEBUG
#define glCheckError() void();
#else
#define glCheckError() CerberusCheck(__FILE__, __LINE__);
#endif

#define GL_CHECK_CALL(X) \
    do { \
        X; \
        glCheckError(); \
    } while(0);

#define GL_CHECK_SET_CALL(value, X) \
    do { \
        value = X; \
        glCheckError(); \
    } while(0);

#define GL_MAKE_CALL(X) do { X; } while(0);
#define GL_MAKE_SET_CALL(value, X) do { value = X; } while(0);

}

#endif