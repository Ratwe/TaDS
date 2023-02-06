#ifndef __LIST_STRUCT_H__
#define __LIST_STRUCT_H__

// структура "узла" связного списка
typedef struct node
{
    int start_column_ind;       // номер компоненты в векторах А и JA
    struct node *next_element;  // указатель на следующий "узел"
} node_t;

// структура связного списка IA
typedef struct list
{
    struct node *ptr;  // указатель на первый "узел"
} list_t;

#endif
