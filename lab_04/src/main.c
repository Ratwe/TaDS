#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "menu.h"
#include "errors.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "free_areas.h"

#define OK 0

int main(void)
{
    setlocale(LC_ALL, "ru_RU.UTF-8");  // РУ-символы

    int error_code = OK;
    arr_stack_t arr_stack = { .length = 0 };  // стек в виде массива
    list_stack_t *list_stack = NULL;          // стек в виде списка
    free_areas_t ptrs = { .len = 0 };         // особождённые области

    while (true)
    {
        short int action;
        print_menu();
        error_code = choose_action(&action);

        if (error_code)
        {
            print_error_message(error_code);
            continue;
        }

        error_code = do_action(action, &arr_stack, &list_stack, &ptrs);

        if (error_code)
        {
            print_error_message(error_code);
            continue;
        }
    }

    return OK;
}
