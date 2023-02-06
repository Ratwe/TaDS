#ifndef __DEFINES_H__
#define __DEFINES_H__

#define READ_OK 1
#define READ_SIZES_OK 2
#define MIN_X 2
#define MAX_X 10000
#define MIN_Y 2
#define MAX_Y 10000
#define MAX_INT 2147483646
#define MAX_PRINT 100
#define MAX_MATRIX_PRINT 100

#define EXIT_SUCCESS 0
#define MODE_ERROR 101
#define INVALID_INPUT 102
#define INVALID_Y_SIZE 103
#define INVALID_X_SIZE 104
#define INVALID_FULLNESS 105
#define MEMORY_ERROR 106
#define SIZE_MATCH_ERROR 107

#endif

#ifdef DEBUG
#define LOG_DEBUG(...) { printf(__VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif
