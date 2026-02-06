#ifndef LOGGING_H
#define LOGGING_H
#include "assert.h"

namespace tartarus {

enum : int {
    INFO = 0,
    DEBUG = 1,
    ERROR = 2,
    FATAL = 3
};

void InitLoggingBuffer();
void ExitLoggingBuffer();

void printLog(const char* file, int line, const char* function, int severity, const char* format,...);

void CerberusCheck(const char* file, int line);

#define SCREAM(...) \
    printLog(__FILE__, \
    __LINE__, \
    __FUNCTION__, \
    FATAL, \
    __VA_ARGS__)

#ifndef NDEBUG
#define LOG(...) \
    printLog(__FILE__, \
    __LINE__, \
    __FUNCTION__, \
    __VA_ARGS__)
#define CHECK(cond) do { assert(cond); } while(0);
#else
#define LOG(...) \
    printLog(__FILE__, \
    __LINE__, \
    __FUNCTION__, \
    __VA_ARGS__) 
#define CHECK(cond) void(0);
#endif

}

#endif