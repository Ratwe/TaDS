#include <stdio.h>

#include "defines.h"
#include "matrix_struct.h"
#include "processing.h"

int composition_std(std_matrix_t *const m1, std_matrix_t *const m2, std_matrix_t *res)
{
    if (m1->xsize != m2->xsize || m1->ysize != m2->ysize)
    {
        printf("Размеры матриц не совпадают!\n");
        return SIZE_MATCH_ERROR;
    }

    int n = res->xsize;
    int m = res->ysize;

    // printf("n, m = %d, %d\n", n, m);
    // printf("sizeof(matrix) = %ld\n", sizeof(res->matrix));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            res->matrix[i][j] = m1->matrix[i][j] + m2->matrix[i][j];

    return EXIT_SUCCESS;
}

int composition_sparce(matrix_t *const m1, matrix_t *const m2, matrix_t *result)
{
    if (m1->xsize != m2->xsize || m1->ysize != m2->ysize)
    {
        printf("Размеры матриц не совпадают!\n");
        return SIZE_MATCH_ERROR;
    }

    node_t *temp_IA1 = get_by_pos(&m1->IA, 0);
    node_t *temp_IA1_next = NULL;
    node_t *temp_IA2 = get_by_pos(&m2->IA, 0);
    node_t *temp_IA2_next = NULL;
    result->curr_size = 0;

    for (int i = 0; i < m1->ysize - 1; i++)
    {
        temp_IA1_next = temp_IA1->next_element;
        temp_IA2_next = temp_IA2->next_element;

        int j1 = temp_IA1->start_column_ind;
        int j2 = temp_IA2->start_column_ind;

        while (j1 < temp_IA1_next->start_column_ind && j2 < temp_IA2_next->start_column_ind)
        {
            int ja1 = m1->JA[j1];
            int ja2 = m2->JA[j2];

            LOG_DEBUG("ja1, ja2 = %d, %d\n", ja1, ja2);

            if (ja1 < ja2)
            {
                result->A[result->curr_size] = m1->A[j1];
                result->JA[result->curr_size] = ja1;
                j1++;
            }
            else if (ja2 < ja1)
            {
                result->A[result->curr_size] = m2->A[j2];
                result->JA[result->curr_size] = ja2;
                j2++;
            }
            else
            {
                result->A[result->curr_size] = m1->A[j1] + m2->A[j2];
                result->JA[result->curr_size] = ja1;
                j1++, j2++;
            }

            result->curr_size++;
        }

        while (j1 < temp_IA1_next->start_column_ind)
        {
            int ja1 = m1->JA[j1];

            result->A[result->curr_size] = m1->A[j1];
            result->JA[result->curr_size] = ja1;

            j1++;
            result->curr_size++;
        }

        while (j2 < temp_IA2_next->start_column_ind)
        {
            int ja2 = m2->JA[j2];

            result->A[result->curr_size] = m2->A[j2];
            result->JA[result->curr_size] = ja2;

            j2++;
            result->curr_size++;
        }

        temp_IA1 = temp_IA1_next;
        temp_IA2 = temp_IA2_next;
    }

    int j1 = temp_IA1->start_column_ind;
    int j2 = temp_IA2->start_column_ind;

    while (j1 < m1->curr_size && j2 < m2->curr_size)
    {
        int ja1 = m1->JA[j1];
        int ja2 = m2->JA[j2];

        LOG_DEBUG("ja1, ja2 = %d, %d\n", ja1, ja2);

        if (ja1 < ja2)
        {
            result->A[result->curr_size] = m1->A[j1];
            result->JA[result->curr_size] = ja1;
            j1++;
        }
        else if (ja2 < ja1)
        {
            result->A[result->curr_size] = m2->A[j2];
            result->JA[result->curr_size] = ja2;
            j2++;
        }
        else
        {
            result->A[result->curr_size] = m1->A[j1] + m2->A[j2];
            result->JA[result->curr_size] = ja1;
            j1++, j2++;
        }

        result->curr_size++;
    }

    while (j1 < m1->curr_size)
    {
        int ja1 = m1->JA[j1];

        result->A[result->curr_size] = m1->A[j1];
        result->JA[result->curr_size] = ja1;

        j1++;
        result->curr_size++;
    }

    while (j2 < m2->curr_size)
    {
        int ja2 = m2->JA[j2];

        result->A[result->curr_size] = m2->A[j2];
        result->JA[result->curr_size] = ja2;

        j2++;
        result->curr_size++;
    }

    return EXIT_SUCCESS;
}
