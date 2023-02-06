#include <stdio.h>

#include "free_areas.h"
#include "list_stack.h"
#include "errors.h"
#include "my_functions.h"

int add_area(free_areas_t *array, list_stack_t *const ptr)
{
    if (!array)
        return ERR_NULL_POINTER;

    if (array->len == MAX_AREAS_NUM)
        return ERR_FULL_ARR;

    array->arr[array->len] = ptr;
    array->len++;

    return OK;
}

void shift(free_areas_t *array, const int index)
{
    array->len--;

    for (int i = index; i < array->len; i++)
        array->arr[i] = array->arr[i + 1];
}

int delete_area(free_areas_t *array, list_stack_t *const ptr)
{
    if (!array)
        return ERR_NULL_POINTER;

    if (!array->len)
        return ERR_EMPTY_ARR;

    for (int i = 0; i < array->len; i++)
    {
        if (array->arr[i] <= ptr && ptr < array->arr[i] + 1)
        {
            shift(array, i);
            break;
        }
    }

    return OK;
}

int print_free_areas(free_areas_t *array)
{
    if (!array->len)
        return ERR_EMPTY_ARR;

    putws(L"\nАдреса освобожденных областей:\n");
    for (int i = 0; i < array->len; i++)
        fwprintf(stdout, L"%p\n", (void *) array->arr[i]);
        
    return OK;
}