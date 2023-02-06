#include <stdio.h>

#include "defines.h"
#include "matrix_struct.h"
#include "list_struct.h"

void matrix_print(std_matrix_t m1, std_matrix_t m2)
{
    if (m1.xsize * m1.ysize > MAX_MATRIX_PRINT)
    {
        printf("Матрица не будет выведена на экран,\n"
            "так как размер превышает %d элементов.\n", MAX_MATRIX_PRINT);
        return;
    }

    printf("\n\n Первая матрица:\n");
    for (int i = 0; i < m1.ysize; i++)
    {
        for (int j = 0; j < m1.xsize; j++)
            printf("%3d ", m1.matrix[i][j]);

        printf("\n");
    }

    if (m2.xsize * m2.ysize > MAX_MATRIX_PRINT)
    {
        printf("Матрица не будет выведена на экран,\n"
        "так как размер превышает %d элементов.\n", MAX_MATRIX_PRINT);
        return;
    }

    printf("\n\n Вторая матрица: \n");
    for (int i = 0; i < m2.ysize; i++)
    {
        for (int j = 0; j < m2.xsize; j++)
            printf("%3d ", m2.matrix[i][j]);

        printf("\n");
    }

    printf("\n");
}

void sparce_matrix_print(matrix_t m1, matrix_t m2)
{
    if (m1.curr_size == 0)
    {
        printf("\n\nРазреженный вектор A первой матрицы пуст.");
        return;
    }

    if (m1.curr_size > MAX_PRINT)
    {
        printf("\n\nРезультат вычислений первой разреженной матрицы не будет выведен на экран,\n"
            "так как он содержит более %d элементов.", MAX_PRINT);
        return;
    }

    printf("\nРазреженный вектор A первой матрицы: ");

    for (int i = 0; i < m1.curr_size; i++)
        printf("%3d ", m1.A[i]);

    printf("\nМассив индексов столбцов JA первой матрицы: ");

    for (int i = 0; i < m1.curr_size; i++)
        printf("%3d ", m1.JA[i]);

    if (m2.curr_size == 0)
    {
        printf("\n\nРазреженный вектор A второй матрицы пуст.");
        return;
    }

    if (m2.curr_size > MAX_PRINT)
    {
        printf("\n\nРезультат вычислений второй разреженной матрицы не будет выведен на экран,\n"
            "так как он содержит более %d элементов.", MAX_PRINT);
        return;
    }

    printf("\nРазреженный вектор A второй матрицы: ");

    for (int i = 0; i < m2.curr_size; i++)
        printf("%3d ", m2.A[i]);

    printf("\nМассив индексов столбцов JA второй матрицы: ");

    for (int i = 0; i < m2.curr_size; i++)
        printf("%3d ", m2.JA[i]);

    printf("\n");
}

void matrix_res_print(std_matrix_t res)
{
    if (res.xsize * res.ysize > MAX_MATRIX_PRINT)
    {
        printf("Матрица не будет выведена на экран,\n"
            "так как размер превышает %d элементов.\n", MAX_MATRIX_PRINT);
        return;
    }

    printf("\n\n Матрица результата:\n");
    for (int i = 0; i < res.ysize; i++)
    {
        for (int j = 0; j < res.xsize; j++)
            printf("%3d ", res.matrix[i][j]);

        printf("\n");
    }

    printf("\n");
}

void sparce_matrix_res_print(matrix_t res)
{
    if (res.curr_size == 0)
    {
        printf("\n\nРазреженный вектор A матрицы результата пуст.");
        return;
    }

    if (res.curr_size > MAX_PRINT)
    {
        printf("\n\nРезультат вычислений разреженной матрицы результата не будет выведен на экран,\n"
            "так как он содержит более %d элементов.\n", MAX_PRINT);
        return;
    }

    printf("\nРазреженный вектор A матрицы результата: ");

    for (int i = 0; i < res.curr_size; i++)
        printf("%3d ", res.A[i]);

    printf("\nМассив индексов столбцов JA матрицы результата: ");

    for (int i = 0; i < res.curr_size; i++)
        printf("%3d ", res.JA[i]);

    printf("\n");
}

void print_method_comparison(long std_time, long sparce_time, matrix_t m1, matrix_t m2)
{
    printf("\n\nЗаполненность матрицы 1: %f\%% \n", 100.0 * m1.curr_size / (m1.xsize * m1.ysize));
    printf("Заполненность матрицы 2: %f\%% \n\n", 100.0 * m2.curr_size / (m2.xsize * m2.ysize));

    printf("Время перемножения матриц в 'обычном' виде: %ld мс\n", std_time);
    printf("Время перемножения матриц в разреженном виде: %ld мс\n", sparce_time);
    if (std_time > sparce_time)
        printf("Эффективность второго способа выше в %f раз\n\n", (double) std_time / (double) sparce_time);
    else
        printf("Эффективность второго способа ниже в %f раз\n\n", (double) sparce_time / (double) std_time);


    long v1 = (m1.xsize * m1.ysize + m2.xsize * m2.ysize + 4) * sizeof(int);
    long v2 = ((m1.curr_size + m2.curr_size + 3) * 2) * sizeof(int) + (m1.ysize + m2.ysize) * sizeof(node_t);

    printf("Память, занимаемая обычными матрицами: %ld\n", v1);
    printf("Память, занимаемая разреженной матрицей: %ld\n", v2);
    if (v1 > v2)
        printf("Эффективность второго способа хранения выше в %f раз\n\n", (double) v1 / (double) v2);
    else
        printf("Эффективность второго способа хранения ниже в %f раз\n\n", (double) v2 / (double) v1);



}
