#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "list_stack.h"
#include "errors.h"
#include "free_areas.h"

int ls_pop(list_stack_t **stack, wint_t *const element)
{
    if (!stack)
        return ERR_NULL_POINTER;

    if (!*stack)
        return ERR_EMPTY_STACK;

    list_stack_t *prev = *stack;
    *stack = (*stack)->prev;

    *element = prev->data;
    free(prev);

    return OK;
}

int ls_push(list_stack_t **stack, const wint_t element)
{
    if (!stack)
        return ERR_NULL_POINTER;

    if (*stack && (*stack)->index + 1 == MAX_LIST_LEN)
        return ERR_FULL_STACK;

    list_stack_t *node = malloc(sizeof(list_stack_t));
    node->data = element;
    node->index = (!*stack) ? 0 : (*stack)->index + 1;
    node->prev = *stack;
    *stack = node;

    return OK;
}

int ls_print(list_stack_t **stack)
{
    if (!*stack)
        return ERR_EMPTY_STACK;

    list_stack_t *node = NULL;
    while (*stack)
    {
        fwprintf(stdout, L"%p  ", (void *) (*stack));
        fwprintf(stdout, L"%18lc\n", (*stack)->data);

        wint_t el;
        ls_pop(stack, &el);
        ls_push(&node, el);
    }

    while (node)
    {
        wint_t el;
        ls_pop(&node, &el);
        ls_push(stack, el);
    }

    fwprintf(stdout, L"\nПамять (байт): %ld\n",
             sizeof(list_stack_t) * ((*stack)->index + 1));

    return OK;
}
