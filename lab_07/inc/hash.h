#ifndef __HASH__H__
#define __HASH__H__

typedef struct set set_t;

struct set
{
  int key;      // ключ
  int data;     // значение
  set_t *next;  // указатель на след. элемент
};


void init_array(set_t **array, int *size);

void insert(set_t **arr, int key, int data, int size);

void print_ht(set_t *arr, int size);

int hash_func(int key, int size);

#endif
