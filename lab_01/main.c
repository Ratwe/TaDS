#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <math.h>

#define MAX_INT_LEN 31
#define MAX_NORMAL_LEN 39
#define MANTISS_SIZE 30
#define EXP_SIZE 5
#define MAX_EXP 99999
#define REAL_MASK "^([+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?||[.][0-9]+([eE][+-]?[0-9]+)?)$)"
#define INTEGER_MASK "^([+-]?[0-9]+)$"
#define RES_MANTISS_SIZE MANTISS_SIZE * 2
#define REAL_START real_num.start_index
#define INTEGER_START integer_num.start_index
#define RES_START REAL_START + INTEGER_START

#define INPUT_REAL_NUM_ERROR 101
#define INPUT_INTEGER_NUM_ERROR 102
#define REAL_MASK_ERROR 103
#define INTEGER_MASK_ERROR 104
#define EXP_SIZE_ERROR 105
#define MANTISS_SIZE_ERROR 106
#define INT_SIZE_ERROR 107
#define REAL_SIZE_ERROR 108
#define EMPTY_INPUT_ERROR 109
#define ZERO_ERROR 110

// Структура числа в нормальном виде
struct real_t
{
    int m_sign;
    int mantiss[MANTISS_SIZE];
    int exp_sign;
    int exp;
    int start_index;
};

struct res_t
{
    int m_sign;
    int mantiss[RES_MANTISS_SIZE];
    int exp_sign;
    int exp;
    int start_index;
};

struct int_t
{
    int sign;
    int digits[MANTISS_SIZE];
    int start_index;
};

typedef struct real_t real_t;
typedef struct int_t int_t;
typedef struct real_t res_t;

// Перевод корректных числовых данных в структуры
int process_nums(char *real_num_s, char *integer_num_s, real_t *real_num, int_t *integer_num)
{
    char *ptr = real_num_s;
    int i = 0;
    int exp_diff = 0;

    if (*ptr == '-')
    {
        real_num->m_sign = -1;
        ptr++;
    }
    else if (*ptr == '+')
        ptr++;


    while (*ptr != 'e' && *ptr != 'E' && *ptr != '.' && *ptr != '\0')
    {
        real_num->mantiss[MANTISS_SIZE - 1 - i] = *ptr - '0';
        i++;
        ptr++;

        if (i > MANTISS_SIZE)
            return MANTISS_SIZE_ERROR;
    }

    switch (*ptr)
    {
        case '.':
            ptr++;

            while (*ptr != 'e' && *ptr != 'E' && *ptr != '\0')
            {
                real_num->mantiss[MANTISS_SIZE - 1 - i] = *ptr - '0';
                i++;
                ptr++;
                exp_diff--;

                if (i > MANTISS_SIZE)
                    return MANTISS_SIZE_ERROR;
            }

            if ((*ptr != 'e') && (*ptr != 'E'))
                break;
            // иначе работаем так, будто там экспонента

        case 'e':
        case 'E':
            ptr++;

            if (*ptr == '-')
            {
                real_num->exp_sign = -1;
                ptr++;
            }
            else if (*ptr == '+')
                ptr++;

            int pw = strlen(ptr);
            while (*ptr != '\0')
            {
                real_num->exp += (*ptr - '0') * (int)pow(10, pw-- - 1);
                ptr++;
            }

            if (abs(real_num->exp) > MAX_EXP)
                return EXP_SIZE_ERROR;

            break;
    }

    if (exp_diff < 0)
        exp_diff--;

    real_num->exp += exp_diff * real_num->exp_sign;
    real_num->start_index = MANTISS_SIZE - i;

    ptr = integer_num_s;
    if (*ptr == '-')
    {
        integer_num->sign = -1;
        ptr++;
    }
    else if (*ptr == '+')
        ptr++;


    i = 0;
    while (*ptr != '\0')
    {
        integer_num->digits[MANTISS_SIZE - 1 - i] = *ptr - '0';
        i++;
        ptr++;
    }
    integer_num->start_index = MANTISS_SIZE - i;

#ifdef DEBUG
printf("real_num:\nm_sign: %d\nmantiss: ", real_num->m_sign);
for (int i = real_num->start_index; i < MANTISS_SIZE; i++)
    printf("%d", real_num->mantiss[i]);
printf("\nexp_sign: %d\nexp: %d\nstart_index: %d\n\n", real_num->exp_sign, real_num->exp, real_num->start_index);

printf("integer_num:\nsign: %d\ndigits: ", integer_num->sign);
for (int i = integer_num->start_index; i < MANTISS_SIZE; i++)
    printf("%d", integer_num->digits[i]);
printf("\nstart_index: %d\n\n", integer_num->start_index);
#endif

    return EXIT_SUCCESS;
}

// Функция ввода и его проверки на корректность
int input(char *real_num_s, char *integer_num_s)
{
    printf("Оба числа должны быть отличны от нуля\n");

    printf("Введите действительное число: ");
    if (fgets(real_num_s, MAX_NORMAL_LEN + 2, stdin) == NULL)
        return INPUT_REAL_NUM_ERROR;

    size_t real_num_len = strlen(real_num_s);

    if (real_num_s[real_num_len - 1] != '\n')
    {
        printf("Слишком длинное действительное число!\n");
        return REAL_SIZE_ERROR;
    }
    if (real_num_s[0] == '\n')
    {
        printf("Пустая строка!\n");
        return EMPTY_INPUT_ERROR;
    }

    real_num_s[strcspn(real_num_s, "\n")] = 0;  // удаление \n


    printf("Введите целое число: ");
    if (fgets(integer_num_s, MAX_INT_LEN + 2, stdin) == NULL)
        return INPUT_INTEGER_NUM_ERROR;

    size_t integer_num_len = strlen(integer_num_s);

    if (integer_num_s[integer_num_len - 1] != '\n')
    {
        printf("Слишком длинное целое число!\n");
        return INT_SIZE_ERROR;
        // +99999999999999999999999999999.9e+99999
        // +0.1299999999999999999999999999990E+32
    }
    else if (integer_num_s[0] != '-' && integer_num_s[0] != '+' && integer_num_s[integer_num_len - 1] != '\n')
    {
        printf("Слишком длинное целое число!\n");
        return INT_SIZE_ERROR;
    }

    if (integer_num_s[0] == '\n')
    {
        printf("Пустая строка!\n");
        return EMPTY_INPUT_ERROR;
    }

    integer_num_s[strcspn(integer_num_s, "\n")] = 0;  // удаление \n


#ifdef DEBUG
printf("%s\n%s\n\n", real_num_s, integer_num_s);
#endif

    // Проверка на корректность через маску
    regex_t regex;

    regcomp(&regex, INTEGER_MASK, REG_EXTENDED);  // Целого числа
    if (regexec(&regex, integer_num_s, 0, NULL, 0) == REG_NOMATCH)
        return INTEGER_MASK_ERROR;

    regcomp(&regex, REAL_MASK, REG_EXTENDED);  // Действительного числа
    if (regexec(&regex, real_num_s, 0, NULL, 0) == REG_NOMATCH)
        return REAL_MASK_ERROR;

    return EXIT_SUCCESS;
}

int process(char *real_num_s, char *integer_num_s, char *res_num_s)
{
    struct real_t real_num = {1, { 0 }, 1, 0, 0};
    struct int_t integer_num = {1, { 0 }, 0};
    struct res_t res_num = {1, { 0 }, 1, 0, MANTISS_SIZE};

    int error_code = 0;
    if ((error_code = process_nums(real_num_s, integer_num_s, &real_num, &integer_num)))
        return error_code;

    int count = 0;
    for (int i = 0; i < MANTISS_SIZE; i++)
        if (real_num.mantiss[i] != 0)
            count++;

    if (!count)
    {
        printf("Введён нуль!\n");
        return ZERO_ERROR;
    }

    count = 0;
    for (int i = 0; i < MANTISS_SIZE; i++)
        if (integer_num.digits[i] != 0)
            count++;

    if (!count)
    {
        printf("Введён нуль!\n");
        return ZERO_ERROR;
    }

    res_num.m_sign = real_num.m_sign * integer_num.sign;
    res_num.exp_sign = real_num.exp_sign;
    res_num.exp = real_num.exp;

#ifdef DEBUG
printf("REAL_START: %d\n", REAL_START);
printf("INTEGER_START: %d\n", INTEGER_START);
#endif


    for (int i = REAL_START; i < MANTISS_SIZE; i++)
        for (int j = INTEGER_START, rest = 0; j < MANTISS_SIZE || rest; j++)
        {
            int cur = res_num.mantiss[i + j] + real_num.mantiss[i] * (j < MANTISS_SIZE ? integer_num.digits[j] : 0) + rest;
            res_num.mantiss[i + j] = cur % 10;
            // printf("mantiss[%d] = %d\n", i + j, cur % 10);
            rest = cur / 10;
        }

#ifdef DEBUG
printf("RES_START: %d\n", RES_START);
printf("RES_MANTISS_SIZE: %d\n", RES_MANTISS_SIZE);
printf("res_num_mantiss: \n");
for (int i = 0; i < RES_MANTISS_SIZE; i++)
    printf("%d", res_num.mantiss[i]);
printf("\n");
#endif

    int i = RES_MANTISS_SIZE - 1;
    res_num.start_index = RES_START;

    // перевод нулей: 500e0 -> 5e2
    while (res_num.mantiss[i] == 0)
    {
        for (int j = i; j > 0; j--)
        {
            // printf("%d = %d\n", res_num.mantiss[j], res_num.mantiss[j - 1]);
            res_num.mantiss[j] = res_num.mantiss[j - 1];  // сдвиг вправо
        }
        // res_num.exp--;

        res_num.start_index++;
        // printf("exp: %d\n", res_num.exp);
    }

    // printf("res_num.mantiss[MANTISS_SIZE - 1]: %d\n", res_num.mantiss[MANTISS_SIZE - 1]);
    // printf("res_num.mantiss[MANTISS_SIZE]: %d\n", res_num.mantiss[MANTISS_SIZE]);
    if (res_num.mantiss[MANTISS_SIZE - 1] >= 5)
        res_num.mantiss[MANTISS_SIZE]++;  // округление 30-й цифры 5|9...97 -> 5|0...08

    i = MANTISS_SIZE;
    // перевод десятков 9997 -> 0008
    while (res_num.mantiss[i] == 10 && i < RES_MANTISS_SIZE)
    {
        res_num.mantiss[i++] = 0;

        if (i == RES_MANTISS_SIZE)  // переполнение, 00000|1 e0 -> 00001 e1
        {
            for (int j = MANTISS_SIZE + 1; j < RES_MANTISS_SIZE; j++)
                res_num.mantiss[j - 1] = res_num.mantiss[j];  // сдвиг влево

            res_num.mantiss[RES_MANTISS_SIZE - 1] = 1;
            res_num.exp++;
        }

        res_num.mantiss[i]++;
    }

#ifdef DEBUG
printf("start_index: %d\n", res_num.start_index);
printf("new res_num_mantiss: \n");
for (int i = 0; i < RES_MANTISS_SIZE; i++)
    printf("%d", res_num.mantiss[i]);
printf("\n");

for (int i = res_num.start_index; i < RES_MANTISS_SIZE; i++)
    printf("%d", res_num.mantiss[i]);
printf("\n");
#endif

    // перевод нулей в E: 000053 e0 -> 53 e4
    i = res_num.start_index;
    while (i < RES_MANTISS_SIZE && res_num.mantiss[i] == 0)
    {
        i++;
        res_num.exp++;
        res_num.start_index++;
    }

    if (real_num.exp < 0)
        res_num.exp++;

    res_num.exp += RES_MANTISS_SIZE - res_num.start_index;

#ifdef DEBUG
printf("exp += %d - %d\n", RES_MANTISS_SIZE, res_num.start_index);
printf("exp: %d\n", res_num.exp);
#endif

    if (res_num.exp > MAX_EXP)
        return EXP_SIZE_ERROR;

    // перевод структуры в строку
    char *ptr = res_num_s;

    if (res_num.m_sign >= 0)
        *ptr = '+';
    else
        *ptr = '-';
    ptr++;

    *(ptr++) = '0';
    *(ptr++) = '.';


    for (int i = RES_MANTISS_SIZE - 1; i >= res_num.start_index + fmax(0, res_num.exp - MANTISS_SIZE); i--, ptr++)
    {
        if (i == res_num.start_index - 1 && res_num.mantiss[i] == 0)
            break;
        *ptr = res_num.mantiss[i] + '0';
    }

    *ptr = 'E';
    ptr++;

    if (res_num.exp >= 0)
        *ptr = '+';
    else
        *ptr = '-';
    ptr++;

    int temp_exp = res_num.exp;
    count = 0;

    while (temp_exp /= 10)
        count++;

    *(ptr + count + 1) = '\0';

    temp_exp = abs(res_num.exp);
    while (count >= 0)
    {
#ifdef DEBUG
printf("temp_exp div 10: %d\n", temp_exp % 10);
#endif
        *(ptr + count--) = temp_exp % 10 + '0';
        temp_exp /= 10;
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    int error_code = EXIT_SUCCESS;
    char real_num_s[MAX_NORMAL_LEN + 2];
    char integer_num_s[MAX_INT_LEN + 2];
    char res_num[MAX_NORMAL_LEN];

    if ((error_code = input(real_num_s, integer_num_s)))
    {
        printf("Невозможно провести расчёт!\nВведены некорректные данные!\n");
        return error_code;
    }

    if ((error_code = process(real_num_s, integer_num_s, res_num)))
    {
        printf("Невозможно провести расчёт!\nВведены некорректные данные!\n");
        return error_code;
    }

    printf("Результат: %s\n", res_num);

    return error_code;
}
