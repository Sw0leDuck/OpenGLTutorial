#include "Common/Logging.h"
#include "Common/Algorithm.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdarg.h"

namespace tartarus {

namespace global {
    // used only in this file, printLog might be called from different thread
    // currently, the only thread running is the main
    thread_local char* buffer;
}

#define DEFAULT_LOG_BUFFER_SIZE 256

static const char* severityNames[] = {
    "INFO",
    "DEBUG",
    "ERROR",
    "FATAL"
};

void InitLoggingBuffer(){
    global::buffer = (char*)calloc(DEFAULT_LOG_BUFFER_SIZE, 1);
}

void ExitLoggingBuffer(){
    free(global::buffer);
}

void printLog(const char* file, 
        int line, 
        const char* function,
        int severity,
        const char* format,
        ...) {
    sprintf(global::buffer, "%s [%s:%d] - %s - ", severityNames[severity], file, line, function);

    va_list args;
    va_start(args, format);
    vsprintf(global::buffer+calculateStringLength(global::buffer), format, args);
    va_end(args);

    int finalLength = calculateStringLength(global::buffer);
    puts(global::buffer);
    while(finalLength--)
        global::buffer[finalLength] = '\0';
}

}