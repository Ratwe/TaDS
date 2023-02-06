#include <stdio.h>
#include <wchar.h>

#include "arr_stack.h"
#include "errors.h"

int as_pop(arr_stack_t *stack, wint_t *const element)
{
    if (!stack->length)
        return ERR_EMPTY_STACK;

    stack->length--;
    *element = stack->array[stack->length];
    return OK;
}

int as_push(arr_stack_t *stack, const wint_t element)
{
    if (stack->length == MAX_ARR_LEN)
        return ERR_FULL_STACK;

    stack->array[stack->length] = element;
    stack->length++;
    return OK;
}

int as_print(arr_stack_t *stack)
{
    if (!stack->length)
        return ERR_EMPTY_STACK;

    arr_stack_t tmp = { .length = 0 };
    while (stack->length)
    {
        wint_t el;
        as_pop(stack, &el);
        as_push(&tmp, el);
        fwprintf(stdout, L"%lc\n", el);
    }

    while (tmp.length)
    {
        wint_t el;
        as_pop(&tmp, &el);
        as_push(stack, el);
    }

    fwprintf(stdout, L"\nСтек занимает %ld байт памяти\n", sizeof(*stack));

    return OK;
}
