#ifndef __PRINT_H__
#define __PRINT_H__

void matrix_print(std_matrix_t m1, std_matrix_t m2);

void sparce_matrix_print(matrix_t m1, matrix_t m2);

void matrix_res_print(std_matrix_t res);

void sparce_matrix_res_print(matrix_t res);

void print_method_comparison(long std_time, long sparce_time, matrix_t m1, matrix_t m2);

#endif
