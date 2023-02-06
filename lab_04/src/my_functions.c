#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <wchar.h>

#include "my_functions.h"
#include "errors.h"

size_t my_strlen(const char *const str)
{
    size_t count = 0;
    size_t len = 0;

    while (str[count] != '\0')
    {
        len++;
        count++;

        if (str[count] < 0)
            count++;
    }

    return len;
}

int read_wstr(wchar_t *const str, const int max_len, FILE *stream)
{
    if (!fgetws(str, max_len, stream))
        return ERR_FGETS;

    size_t byte_len = wcslen(str);

    if (L'\n' == str[byte_len - 1])
        str[byte_len - 1] = '\0';
    else
    {
        wclear_stdin();
        return ERR_STR_READ;
    }

    return READ_OK;
}

int read_str(char *const str, const int max_len, FILE *stream)
{
    if (!fgets(str, max_len, stream))
        return ERR_FGETS;

    size_t byte_len = strlen(str);

    if ('\n' == str[byte_len - 1])
        str[byte_len - 1] = '\0';
    else
    {
        clear_stdin();
        return ERR_STR_READ;
    }

    return READ_OK;
}

void wclear_stdin(void)
{
    wint_t ch;
    do
    {
        ch = getwchar();
    } while (ch != '\n' && ch != WEOF);
}
void clear_stdin(void)
{
    char ch;
    do
    {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

int read_uint(uint *const unint)
{
    long long int llint;

    if (scanf("%lld", &llint) != 1)
        return ERR_NONINTEGER;

    if (llint < 0 || llint > UINT_MAX)
        return ERR_NONUINTEGER;

    *unint = (uint) llint;

    return OK;
}

int read_int(int *const integer)
{
    long long int llint;

    if (fwscanf(stdin, L"%lld", &llint) != 1)
        return ERR_NONINTEGER;

    if (llint < INT_MIN || llint > INT_MAX)
        return ERR_NONINTEGER;

    *integer = (int) llint;

    return OK;
}

uint my_round(double number)
{
    if (number < 0)
        number = - number;

    double frac = number - (uint) number;

    if (frac < 0.5)
        return (uint) number;
    else
        return (uint) number + 1;
}

int putws(const wchar_t *ws)
{
    return fputws(ws, stdout);
}
