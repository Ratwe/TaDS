#ifndef __MY_FUNCTIONS_H__

#define __MY_FUNCTIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#define READ_OK 0
#define ERR_FGETS -1
#define ERR_STR_READ -2

typedef unsigned int uint;

size_t my_strlen(const char *const str);

int read_wstr(wchar_t *const str, const int max_len, FILE *stream);

int read_str(char *const str, const int max_len, FILE *stream);

void clear_stdin(void);

void wclear_stdin(void);

int read_uint(uint *const unint);

int read_int(int *const integer);

uint my_round(double number);

int putws(const wchar_t *ws);

#endif
