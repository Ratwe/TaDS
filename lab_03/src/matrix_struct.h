#ifndef __MATRIX_STRUCT_H__
#define __MATRIX_STRUCT_H__

#include "list_struct.h"

// структура разреженной матрицы
typedef struct matrix
{
    int xsize;      // кол-во столбцов в матрице
    int ysize;      // кол-во строк в матрице
    int curr_size;  // кол-во ненулевых элементов

    int *A;         // вектор, хранящий значения ненулевых элементов
    int *JA;        // вектор, хранящий номера столбцов для элементов из А
    list_t IA;      // связный список, в элементе Nk которого находится
                    // номер компонент в A и AJ, с которых начинается
                    // описание строки Nk матрицы A
} matrix_t;


// структура матрицы в обычном виде
typedef struct std_matrix
{
    int **matrix;   // матрица элементов
    int xsize;      // кол-во столбцов в матрице
    int ysize;      // кол-во строк в матрице
} std_matrix_t;

#endif
