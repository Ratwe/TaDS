#include <stdio.h>

#include "matrix_struct.h"
#include "defines.h"

int read_sizes(matrix_t *m1, matrix_t *m2)
{
    long curr_size;

    printf("Введите количество строк и столбцов (от 2 до 10.000) первой матрицы: ");
    if (scanf("%d %d", &m1->ysize, &m1->xsize) != READ_SIZES_OK)
        return INVALID_INPUT;

    if (m1->ysize < MIN_Y || m1->ysize > MAX_Y)
    {
        printf("Некорректное количество строк.\n");
        return INVALID_Y_SIZE;
    }

    if (m1->xsize < MIN_X || m1->xsize > MAX_X)
    {
        printf("Некорректное количество столбцов.\n");
        return INVALID_X_SIZE;
    }

    printf("Введите, сколько ненулевых элементов будет содержаться в матрице: ");
    if (scanf("%ld", &curr_size) != READ_OK)
        return INVALID_INPUT;

    if (curr_size > MAX_INT)
    {
        printf("Заполненность не должна превышать %d элементов.\n", MAX_INT);
        return INVALID_INPUT;
    }

    m1->curr_size = curr_size;
    long long size = (long long)m1->xsize * m1->ysize;

    if (m1->curr_size < 1 || m1->curr_size > size)
    {
        printf("Некорректный ввод количества ненулевых элементов в матрице.\n");
        return INVALID_FULLNESS;
    }


    printf("Введите количество строк и столбцов (от 2 до 10.000) второй матрицы: ");
    if (scanf("%d %d", &m2->ysize, &m2->xsize) != READ_SIZES_OK)
        return INVALID_INPUT;

    if (m2->ysize < MIN_Y || m2->ysize > MAX_Y)
    {
        printf("Некорректное количество строк.\n");
        return INVALID_Y_SIZE;
    }

    if (m2->xsize < MIN_X || m2->xsize > MAX_X)
    {
        printf("Некорректное количество столбцов.\n");
        return INVALID_X_SIZE;
    }

    printf("Введите, сколько ненулевых элементов будет содержаться в матрице: ");
    if (scanf("%ld", &curr_size) != READ_OK)
        return INVALID_INPUT;

    if (curr_size > MAX_INT)
    {
        printf("Заполненность не должна превышать %d элементов.\n", MAX_INT);
        return INVALID_INPUT;
    }

    m2->curr_size = curr_size;
    size = (long long) m2->xsize * m2->ysize;

    if (m2->curr_size < 1 || m2->curr_size > size)
    {
        printf("Некорректный ввод количества ненулевых элементов в матрице.\n");
        return INVALID_FULLNESS;
    }

    return EXIT_SUCCESS;
}

int read_matrix(std_matrix_t *std_matrix, const int maxsize)
{
    for (int i = 0; i < std_matrix->ysize; i++)
        for (int j = 0; j < std_matrix->xsize; j++)
            std_matrix->matrix[i][j] = 0;

    for (int i = 0; i < maxsize; i++)
    {
        int numb, i1, j1;

        printf("Введите отличный от нуля элемент матрицы: ");
        if (scanf("%d", &numb) != READ_OK)
            return INVALID_INPUT;

        printf("Введите номер строки этого элемента): ");
        if (scanf("%d", &i1) != READ_OK)
            return INVALID_INPUT;

        if (i1 < 0 || i1 >= std_matrix->ysize)
        {
            printf("Номер строки превышает максимальный номер строки в матрице.\n");
            return INVALID_INPUT;
        }

        printf("Введите номер столбца этого элемента: ");
        if (scanf("%d", &j1) != READ_OK)
            return INVALID_INPUT;

        if (j1 < 0 || j1 >= std_matrix->xsize)
        {
            printf("Номер столбца превышает максимальный номер столбца в матрице.\n");
            return INVALID_INPUT;
        }

        std_matrix->matrix[i1][j1] = numb;
    }

    return EXIT_SUCCESS;
}
