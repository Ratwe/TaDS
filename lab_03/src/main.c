#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "defines.h"
#include "matrix_struct.h"
#include "list_struct.h"
#include "read.h"
#include "processing.h"
#include "memory_utils.h"
#include "print.h"
#include "composition.h"

int main()
{
    matrix_t sparce_m1, sparce_m2, sparce_res;
    std_matrix_t std_m1, std_m2, std_res;
    list_t m1_list, m2_list, res_list;

    printf(
        "Данная программа складывает две матрицы двумя способами:\n"
        "a) С помощью алгоритма для сложения двух разреженных матриц\n"
        "б) С помощью алгоритма для сложения двух обычных матриц\n"
        "Введите 1, если хотите задать обе матрицы случайно.\n"
        "Введите 2, если хотите вручную ввести значения матриц.\n"
        "Ввод: ");

    int mode, code_error;
    if (scanf("%d", &mode) != READ_OK)
    {
        printf("Введено неправильное кол-во параметров!\n");
        return INVALID_INPUT;
    }

    if (mode < 1 || mode > 2)
    {
        printf("Такого пункта нет!\n");
        return MODE_ERROR;
    }

    if ((code_error = read_sizes(&sparce_m1, &sparce_m2)))
        return code_error;

    sparce_res.xsize = sparce_m1.xsize;
    sparce_res.ysize = 1;

    if ((code_error = init_std_matrix(&std_m1, sparce_m1.xsize, sparce_m1.ysize)))
    {
        free_memory(&std_m1);
        return code_error;
    }

    if ((code_error = init_std_matrix(&std_m2, sparce_m2.xsize, sparce_m2.ysize)))
    {
        free_memory(&std_m2);
        return code_error;
    }

    if ((code_error = init_std_matrix(&std_res, sparce_m1.xsize, sparce_m1.ysize)))
    {
        free_memory(&std_res);
        return code_error;
    }

    int *A_m1 = malloc(sizeof(int) * sparce_m1.curr_size);
    int *JA_m1 = malloc(sizeof(int) * sparce_m1.curr_size);
    int *A_m2 = malloc(sizeof(int) * sparce_m2.curr_size);
    int *JA_m2 = malloc(sizeof(int) * sparce_m2.curr_size);
    int *A_res = malloc(sizeof(int) * (sparce_m1.curr_size + sparce_m2.curr_size));  // памяти нужно меньше
    int *JA_res = malloc(sizeof(int) * (sparce_m1.curr_size + sparce_m2.curr_size));

    if ((code_error = init_sparce_matrix(&sparce_m1, A_m1, JA_m1, &m1_list)))
    {
        free_std_matrix(&std_m1, &std_m2, &std_res);
        return code_error;
    }

    if ((code_error = init_sparce_matrix(&sparce_m2, A_m2, JA_m2, &m2_list)))
    {
        free_std_matrix(&std_m1, &std_m2, &std_res);
        return code_error;
    }

    if ((code_error = init_sparce_matrix(&sparce_res, A_res, JA_res, &res_list)))
    {
        free_std_matrix(&std_m1, &std_m2, &std_res);
        return code_error;
    }

    if ((code_error = filling_matrix(&std_m1, &sparce_m1, mode)))
    {
        free_all_memory(&m1_list, &m2_list, &res_list, &std_m1, &std_m2, &std_res);
        return code_error;
    }

    if ((code_error = filling_matrix(&std_m2, &sparce_m2, mode)))
    {
        free_all_memory(&m1_list, &m2_list, &res_list, &std_m1, &std_m2, &std_res);
        return code_error;
    }

    printf("Полученные матрицы:\n");
    matrix_print(std_m1, std_m2);
    printf("Полученные разреженные матрицы:\n");
    sparce_matrix_print(sparce_m1, sparce_m2);

    struct timeval stop_std, start_std, stop_sparce, start_sparce;

    int i = 0;
    while (i++ < 100)
    {
        gettimeofday(&start_std, NULL);
        if ((code_error = composition_std(&std_m1, &std_m2, &std_res)))
            return code_error;
        gettimeofday(&stop_std, NULL);
    }

    matrix_res_print(std_res);

    unsigned long std_time = (stop_std.tv_sec - start_std.tv_sec) * 10000 + stop_std.tv_usec - start_std.tv_usec;
    printf("Время сложения матриц стандартным способом: %lu мс\n", std_time);

    i = 0;
    while (i++ < 100)
    {
        gettimeofday(&start_sparce, NULL);
        if ((code_error = composition_sparce(&sparce_m1, &sparce_m2, &sparce_res)))
            return code_error;
        gettimeofday(&stop_sparce, NULL);
    }

    unsigned long sparce_time = (stop_sparce.tv_sec - start_sparce.tv_sec) * 10000 + stop_sparce.tv_usec - start_sparce.tv_usec;
    printf("Время сложения матриц 'разреженным' способом: %lu мс\n", sparce_time);

    print_method_comparison(std_time, sparce_time, sparce_m1, sparce_m2);

    sparce_matrix_res_print(sparce_res);
}
