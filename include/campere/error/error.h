#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

#define ERR(cond, fmt, ...) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "Compilation error at %s:%d: " fmt "\n", \
                    __FILE__, __LINE__, ##__VA_ARGS__); \
            exit(1); \
        } \
    } while(0) // NOLINT

#endif
