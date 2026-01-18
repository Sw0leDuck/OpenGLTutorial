#include <glad/glad.h>
#include <string>
#include <iostream>
#include "common/error_handler.h"
#include <cstdio>
#include <string.h>

namespace errorHandler {
#define ERROR_DEFAULT_SIZE 512
    char g_error_message[ERROR_DEFAULT_SIZE]; // TODO: use allocator ???

    void Reset() {
        memset(g_error_message, 0, ERROR_DEFAULT_SIZE);
    }

    void Init() {
        Reset();
    }

    void UpdateError(const char *error){
        strcpy(g_error_message, error);
    }

    void PrintError(){
        puts(g_error_message);
        Reset();
    }

    void glCheckError_(const char *file, int line) {
        GLenum errorCode;
        while ((errorCode = glGetError()) != GL_NO_ERROR)
        {
            std::string error;
            switch (errorCode)
            {
                case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
                case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
                case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
                case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
                case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
                case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
                case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            }
            std::cout << error << " | " << file << " (" << line << ")" << std::endl;
        }
    }

} // errorHandler