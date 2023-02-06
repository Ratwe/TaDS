#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "matrix_struct.h"

int new_matrix(std_matrix_t *const matrix)
{
    matrix->matrix = malloc(matrix->ysize * sizeof(int *));

    if (matrix->matrix == NULL)
        return MEMORY_ERROR;

    for (int i = 0; i < matrix->ysize; i++)
    {
        *(matrix->matrix + i) = malloc(matrix->xsize * sizeof(int));

        if (*(matrix->matrix + i) == NULL)
            return MEMORY_ERROR;
    }

    return EXIT_SUCCESS;
}

void free_memory(std_matrix_t *const matrix)
{
    for (int i = 0; i < matrix->ysize; i++)
    {
        free(matrix->matrix[i]);
        matrix->matrix[i] = NULL;
    }

    free(matrix->matrix);
    matrix->matrix = NULL;
}

void free_std_matrix(std_matrix_t *m1, std_matrix_t *m2, std_matrix_t *res)
{
    free_memory(m1);
    free_memory(m2);
    free_memory(res);
}

void free_list(list_t *list)
{
    node_t *curr, *temp;
    curr = list->ptr;

    while (curr->next_element != NULL)
    {
        temp = curr->next_element;
        free(curr);
        curr = temp;
    }

    free(temp);
}

void free_all_memory(list_t *list_matrix, list_t *list_vector, list_t *list_result,
     std_matrix_t *std_matrix, std_matrix_t *std_vector, std_matrix_t *std_result)
{
    free_list(list_matrix);
    free_list(list_vector);
    free_list(list_result);
    free_std_matrix(std_matrix, std_vector, std_result);
}
