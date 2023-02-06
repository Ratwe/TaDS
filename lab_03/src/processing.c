#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "defines.h"
#include "matrix_struct.h"
#include "memory_utils.h"
#include "read.h"

int init_std_matrix(std_matrix_t *matrix, const int xsize, const int ysize)
{
    int code_error;

    matrix->xsize = xsize;
    matrix->ysize = ysize;

    if ((code_error = new_matrix(matrix)))
        return code_error;

    return EXIT_SUCCESS;
}

int init_list_ptrs(int size, list_t *list)
{
    list->ptr = NULL;

    for (int i = 0; i < size; i++)
    {
        node_t *curr_element = malloc(sizeof(node_t));

        if (curr_element == NULL)
        {
            printf("Memory error, try again.");
            return MEMORY_ERROR;
        }

        curr_element->next_element = list->ptr;
        curr_element->start_column_ind = -1;
        list->ptr = curr_element;
    }

    return EXIT_SUCCESS;
}

int init_sparce_matrix(matrix_t *const sparce_matrix, int *const A, int *const JA, list_t *list)
{
    int code_error;

    if (sparce_matrix->ysize != 1)
    {
        if ((code_error = init_list_ptrs(sparce_matrix->xsize, list)))
        {
            free_list(list);
            return code_error;
        }
    }
    else
        list->ptr = NULL;

    sparce_matrix->A = A;
    sparce_matrix->JA = JA;
    sparce_matrix->IA = *list;

    return EXIT_SUCCESS;
}

void random_filling(std_matrix_t *const std_matrix, const int maxsize)
{
    // srand(time(NULL));

    for (int i = 0; i < maxsize; i++)
    {
        int irand = rand() % std_matrix->ysize;
        int jrand = rand() % std_matrix->xsize;

        // do
        // {
        //     irand = abs(rand() * 228) % std_matrix->ysize;
        //     jrand = abs(rand() * 1337) % std_matrix->xsize;
        //     LOG_DEBUG("std_matrix->matrix[%d][%d] = %d\n", irand, jrand, std_matrix->matrix[irand][jrand]);
        // } while (std_matrix->matrix[irand][jrand] != 0);

        // LOG_DEBUG("std_matrix->matrix[%d][%d] = %d\n", irand, jrand, std_matrix->matrix[irand][jrand]);

        if (std_matrix->matrix[irand][jrand] != 0)
        {
            i--;
            continue;
        }

        std_matrix->matrix[irand][jrand] = rand() % 100 + 1;
    }

}

node_t *get_by_pos(const list_t *list, const int pos)
{
    node_t *temp_node = list->ptr;

    for (int i = 0; i < pos; i++)
    {
        if (temp_node->next_element == NULL)
            return temp_node;

        temp_node = temp_node->next_element;
    }

    return temp_node;
}

void change_by_pos(node_t *node, const list_t *list, const int pos)
{
    node_t *temp_node = get_by_pos(list, pos);
    *temp_node = *node;
}

void copy_matrix(std_matrix_t std_matrix, matrix_t *sparce_matrix)
{
    int k = 0;

    for (int i = 0; i < std_matrix.ysize; i++)
    {
        if (sparce_matrix->IA.ptr != NULL)
        {
            node_t *temp_IA = get_by_pos(&sparce_matrix->IA, i);
            temp_IA->start_column_ind = k;
            change_by_pos(temp_IA, &sparce_matrix->IA, i);
        }

        for (int j = 0; j < std_matrix.xsize; j++)
        {
            if (std_matrix.matrix[i][j] != 0)
            {
                sparce_matrix->A[k] = std_matrix.matrix[i][j];
                sparce_matrix->JA[k] = j;
                ++k;
            }
        }
    }

    sparce_matrix->curr_size = k;
}

int filling_matrix(std_matrix_t *std_matrix, matrix_t *sparce_matrix, const int mode)
{
    if (mode == 2)
    {
        int code_error = read_matrix(std_matrix, sparce_matrix->curr_size) ;

        if (code_error)
            return code_error;
    }
    else
        random_filling(std_matrix, sparce_matrix->curr_size);

    copy_matrix(*std_matrix, sparce_matrix);

    return EXIT_SUCCESS;
}
