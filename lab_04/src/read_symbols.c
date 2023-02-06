#include <stdio.h>
#include <wchar.h>
#include <time.h>

#include "read_symbols.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "my_functions.h"
#include "errors.h"
#include "free_areas.h"

int as_read_symbols(arr_stack_t *stack)
{
    clock_t start, finish, time = 0L;
    int error_code = OK;

    wint_t cur_ch;
    while (!error_code && (cur_ch = getwchar()) != L'\n' && cur_ch != WEOF)
    {
        start = clock();
        error_code = as_push(stack, cur_ch);
        finish = clock();
        time += finish - start;
        if (!error_code)
            fwprintf(stdout, L"\nЭлемент '%lc' успешно добавлен!\n", cur_ch);
    }

    if (!error_code)
        fwprintf(stdout, L"\nВремя работы (в тактах): %ld\n", time);
    else
        wclear_stdin();

    return error_code;
}

int ls_read_symbols(list_stack_t **stack, free_areas_t *ptrs)
{
    clock_t start, finish, time = 0L;
    int error_code = OK;

    wint_t cur_ch;
    while (!error_code && (cur_ch = getwchar()) != L'\n' && cur_ch != WEOF)
    {
        start = clock();
        error_code = ls_push(stack, cur_ch);
        finish = clock();
        time += finish - start;
        delete_area(ptrs, *stack);
        if (!error_code)
            fwprintf(stdout, L"\nЭлемент '%lc' успешно добавлен!\n", cur_ch);
    }

    if (!error_code)
        fwprintf(stdout, L"\nВремя работы (в тактах): %ld\n", time);
    else
        wclear_stdin();

    return error_code;
}
