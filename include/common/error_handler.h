#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

namespace errorHandler {
    
    void UpdateError(const char* error);
    void PrintError();
    void glCheckError_(const char* file, int line);
} // namespace errorHandler

#define glCheckError() errorHandler::glCheckError_(__FILE__, __LINE__);

#endif