#ifndef __ARR_STACK_H__

#define __ARR_STACK_H__

#include <wchar.h>

#define MAX_ARR_LEN 1000

typedef struct
{
    wint_t array[MAX_ARR_LEN];  // массив "длинных" символов в стеке
    int length;                 // кол-во элементов в стеке
} arr_stack_t;

int as_pop(arr_stack_t *stack, wint_t *const element);

int as_push(arr_stack_t *stack, const wint_t element);

int as_print(arr_stack_t *stack);

#endif
