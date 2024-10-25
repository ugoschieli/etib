#ifndef LOG_H
#define LOG_H

void print_debug(const char* format, ...);

void print_error(const char* format, ...);

void logGlError(const char* msg);

#endif // LOG_H
