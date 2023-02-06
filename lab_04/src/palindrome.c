#include <stdio.h>
#include <stdbool.h>
#include <wchar.h>
#include <time.h>

#include "palindrome.h"
#include "my_functions.h"
#include "arr_stack.h"
#include "list_stack.h"
#include "errors.h"

int read_word(arr_stack_t *a_word, list_stack_t **l_word)
{
    int error_code = OK;

    wint_t cur_ch;
    while (!error_code && (cur_ch = getwchar()) != L'\n' && cur_ch != WEOF)
    {
        error_code = as_push(a_word, cur_ch);
        if (!error_code)
            error_code = ls_push(l_word, cur_ch);
    }

    if (error_code)
        wclear_stdin();

    return error_code;
}

bool a_is_palindrome(arr_stack_t *word)
{
    int word_len = word->length;
    arr_stack_t part_2 = { .length = 0 };

    while (part_2.length != word_len / 2)
    {
        wint_t el;
        as_pop(word, &el);
        as_push(&part_2, el);
    }

    wint_t middle = L'\0';
    if (word_len % 2 != 0)
        as_pop(word, &middle);

    while (word->length && part_2.length)
    {
        wint_t word_el, part_2_el;
        as_pop(word, &word_el);
        as_pop(&part_2, &part_2_el);

        if (word_el != part_2_el)
            return false;
    }

    return true;
}

bool l_is_palindrome(list_stack_t **word)
{
    int word_len = (*word)->index + 1;
    list_stack_t *part_2 = NULL;

    while (*word && (*word)->index + 1 != word_len / 2)
    {
        wint_t el;
        ls_pop(word, &el);
        ls_push(&part_2, el);
    }

    wint_t middle = L'\0';
    if (word_len % 2 != 0)
        ls_pop(&part_2, &middle);

    while (*word && part_2)
    {
        wint_t word_el, part_2_el;
        ls_pop(word, &word_el);
        ls_pop(&part_2, &part_2_el);

        if (word_el != part_2_el)
            return false;
    }

    return true;
}

int check_word(void)
{
    int error_code = OK;
    arr_stack_t a_word = { .length = 0};
    list_stack_t *l_word = NULL;

    putws(L"\nВведите строку:\n");
    error_code = read_word(&a_word, &l_word);

    if (!error_code)
    {
        bool a_flag, l_flag;
        clock_t start, finish;


        putws(L"\nПроверка через стек на массиве...\n");
        start = clock();
        a_flag = a_is_palindrome(&a_word);
        finish = clock();
        clock_t time = finish - start;

        fwprintf(stdout, L"Строка %ls палиндромом!\n", a_flag ?
                 L"является" : L"не является");
        fwprintf(stdout, L"Время работы (в тактах): %ld\n", time);


        putws(L"\nПроверка черещ стек на списке...\n");
        start = clock();
        l_flag = l_is_palindrome(&l_word);
        finish = clock();
        time = finish - start;

        fwprintf(stdout, L"Строка %ls палиндромом!\n", l_flag ?
                 L"является" : L"не является");
        fwprintf(stdout, L"Время работы (в тактах): %ld\n", time);
    }

    return error_code;
}
