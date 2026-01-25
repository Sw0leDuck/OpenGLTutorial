#ifndef LOGGING_H
#define LOGGING_H

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

#ifndef NDEBUG
#define LOG(...) \
    printLog(__FILE__, \
    __LINE__, \
    __FUNCTION__, \
    __VA_ARGS__)

#else
#define LOG(SEVERITY) 
#endif

}

// #define glCheckError() errorHandler::glCheckError_(__FILE__, __LINE__);

#endif