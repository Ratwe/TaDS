#ifndef __PROCESSING_H__
#define __PROCESSING_H__

int init_std_matrix(std_matrix_t *const matrix, const int xsize, const int ysize);

int init_list_ptrs(int size, list_t *list);

void free_list(list_t *list);

int init_sparce_matrix(matrix_t *const sparce_matrix, int *const A, int *const JA, list_t *list);

void random_filling(std_matrix_t *const std_matrix, const int maxsize);

node_t *get_by_pos(const list_t *list, const int pos);

void change_by_pos(node_t *node, const list_t *list, const int pos);

void copy_matrix(std_matrix_t std_matrix, matrix_t *sparce_matrix);

int filling_matrix(std_matrix_t *std_matrix, matrix_t *sparce_matrix, const int mode);

#endif
