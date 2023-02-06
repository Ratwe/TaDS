#include <stdio.h>
#include <time.h>

#include "tree.h"
#include "hash.h"
#include "defines.h"
#include "avl_tree.h"

int main(void)
{
    printf("-------------------------------------------------\n");
    printf("           ЛР№7 Деревья, хеш-таблицы\n");
    printf("-------------------------------------------------\n\n");

    int arr[NUMS_COUNT];

    for (int i = 0; i < NUMS_COUNT; i++)
        arr[i] = NUMS_COUNT - i;

    printf("\n\nПолученное выражение:\n");
    printf("%d + (%d * (%d + (%d * (%d + %d) - (%d - %d)) + %d))\n\n",
    arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);

    node_t *root = create_tree(arr);

    printf("\n\nПолученное бинарное дерево:\n");
    print_tree(root, 0);

    printf("\n\nПостфиксный обход:\n");
    postfix_bypass(root, 1);
    printf("\n");

    int tree_arr[MAX_ARR_LEN];
    int ind = 0;
    printf("\n\nИнфиксный обход:\n");
    infix_bypass(root, tree_arr, &ind);
    printf("\n");

    node_t *ddp_tree = create(ddp_tree, 9);
    read_to_tree(&ddp_tree, tree_arr);

    printf("\n\nПолученное ДДП:\n");
    print_tree(ddp_tree, 0);

    node_t *avl_tree = NULL;
    read_to_avl_tree(&avl_tree, tree_arr, 1);

    printf("\n\nПолученное АВЛ-дерево:\n");
    print_tree(avl_tree, 0);

    printf("Результат выражения (по дереву): %d\n\n", root->value);

    // замеры ДДП до самой дальней вершины
    int temp = 0;
    clock_t begin = clock();

    while (temp++ < 1000000)
        get_node_by_value(ddp_tree, 4);

    clock_t end = clock();

    printf("Время для поиска значения на ДДП: %f\n\n", (double)(end - begin) / 1000000);

    temp = 0;
    begin = clock();

    while (temp++ < 1000000)
        get_node_by_value(avl_tree, 4);

    end = clock();

    printf("Время для поиска значения на АВЛ-дереве: %f\n\n", (double)(end - begin) / 1000000);

    set_t *ht = NULL;
    int size = 0;
    init_array(&ht, &size);

    for (int i = 0; i < MAX_ARR_LEN; i++)
        insert(&ht, i * HASH_KEY, arr[i], size);

    print_ht(ht, size);

    int key = 0;
    printf("Введите ключ значения, которое хотите найти: ");
    if (scanf("%d", &key) != 1)
    {
        printf("Ошибка! Требуется целое число.\n");
        return SCANF_ERR;
    }

    temp = 0, ind = key % size;
    begin = clock();

    while (temp++ < 1000000)
        ht[ind].data = ht[ind].data;

    end = clock();

    if (key != ht[ind].key)
    {
        printf("Ошибка! Такого ключа не существует.\n");
        return KEY_ERR;
    }
    printf("Найденное значение: %5d | %d\n\n", ht[ind].key, ht[ind].data);
    printf("Время для поиска значения в хэш-таблице: %f\n\n", (double)(end - begin) / 1000000);

    return EXIT_SUCCESS;
}
