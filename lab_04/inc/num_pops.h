#ifndef __NUM_POPS_H__

#define __NUM_POPS_H__

#include "arr_stack.h"
#include "list_stack.h"
#include "free_areas.h"

int as_num_pop(arr_stack_t *stack, const int num);

int ls_num_pop(list_stack_t **stack, const int num, free_areas_t *ptrs);

#endif