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

} // errorHandler