#ifndef __MENU_H__

#define __MENU_H__

#include "arr_stack.h"
#include "list_stack.h"
#include "free_areas.h"

#define MAX_MENU_ITEM_LEN 2

void print_menu(void);

int choose_action(short int *const action);

void print_error_message(const int code);

int do_action(const short int action, arr_stack_t *a_stack,
              list_stack_t **l_stack, free_areas_t *prts);

#endif
