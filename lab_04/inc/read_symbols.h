#ifndef __READ_SYMBOLS_H__

#define __READ_SYMBOLS_H__

#include "arr_stack.h"
#include "list_stack.h"
#include "free_areas.h"

int as_read_symbols(arr_stack_t *stack);

int ls_read_symbols(list_stack_t **stack, free_areas_t *ptrs);

#endif