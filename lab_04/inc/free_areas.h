#ifndef __FREE_AREAS_H__

#define __FREE_AREAS_H__

#include "list_stack.h"

#define MAX_AREAS_NUM 1000

typedef struct
{
    list_stack_t *arr[MAX_AREAS_NUM];   // массив освобожденных областей
    int len;                            // кол-во элементов в массиве
} free_areas_t;

int add_area(free_areas_t *array, list_stack_t *const ptr);

int delete_area(free_areas_t *array, list_stack_t *const ptr);

int print_free_areas(free_areas_t *array);

#endif
