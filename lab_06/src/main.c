#include <stdio.h>
#include <time.h>

#include "tree.h"
#include "stack.h"
#include "defines.h"

int main(void)
{
    printf("-------------------------------------------------\n");
    printf("           ЛР№6 Бинарное дерево\n");
    printf("-------------------------------------------------\n\n");

    int arr[NUMS_COUNT];

    printf("Введите %d целочисленных значений для A, B, C ... I: ", NUMS_COUNT);
    for (int i = 0; i < NUMS_COUNT; i++)
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Ошибка! Требуется целое число.\n");
            return SCANF_ERR;
        }

    printf("\n\nПолученное выражение:\n");
    printf("%d + (%d * (%d + (%d * (%d + %d) - (%d - %d)) + %d))\n\n",
    arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8]);

    node_t *root = create_tree(arr);

    printf("\n\nПолученное бинарное дерево:\n");
    print_tree(root, 0);

    printf("Префиксный обход:\n");
    prefix_bypass(root);

    printf("\n\nИнфиксный обход:\n");
    infix_bypass(root);

    printf("\n\nПостфиксный обход:\n");
    postfix_bypass(root, 1);
    printf("\n\n");

    int temp = 0;
    clock_t begin = clock();

    while (temp++ < 1000000)
        postfix_bypass(root, 0);

    clock_t end = clock();

    printf("Результат выражения (по дереву): %d\n\n", root->value);
    printf("Время для вычисления выражения по дереву: %f\n\n", (double)(end - begin) / 1000000);

    temp = 0;
    int res = 0;
    begin = clock();

    // while (temp++ < 1000000)
    res = stack_res(arr);

    end = clock();

    printf("Результат выражения (по стеку): %d\n\n", res);
    // printf("Время для вычисления выражения по стеку: %f\n\n", (double)(end - begin) / 1000000);

    int n, val, rc = 0;
    printf("Сколько хотите добавить вершин к новому пустому дереву целых чисел?\n");

    if ((rc = scanf("%d", &n) != 1))
    {
        printf("Ошибка! Требуется целое число.\n");
        return SCANF_ERR;
    }

    if (n > 0)
    {
        printf("Введите значение корневой вершины: ");
        if ((scanf("%d", &val) != 1))
        {
            printf("Ошибка! Требуется целое число.\n");
            return SCANF_ERR;
        }

        begin = clock();

        root = create_node(0, NULL, NULL, NULL, val, ' ');

        node_t *old_node = root;
        temp = 1;
        while (temp++ < n)
        {
            printf("Введите значение %d-й вершины: ", temp);
            if (scanf("%d", &val) != 1)
            {
                printf("Ошибка! Требуется целое число.\n");
                return SCANF_ERR;
            }

            node_t *new_node = create_node(0, old_node, NULL, NULL, val, ' ');
            old_node->left = new_node;
            old_node = new_node;
        }

        printf("\n\nПолученное дерево:\n");
        print_tree(root, 0);
    }


    int m;
    printf("\n\nСколько хотите оставить вершин из дерева целых чисел?\nВвод: ");

    if ((rc = scanf("%d", &m) != 1))
    {
        printf("Ошибка! Требуется целое число.\n");
        return SCANF_ERR;
    }

    if (m > n)
    {
        printf("Ошибка! Невозможно оставить больше узлов, чем есть.\n");
        return WRONG_DELETE;
    }

    if (m > 0)
    {
        node_t *old_node = root;
        node_t *new_node = root;
        m--;

        temp = 0;
        while (temp++ < m)
        {
            new_node = old_node->left;
            old_node = new_node;
        }

        new_node->left = NULL;

        print_tree(root, 0);
    }

    return EXIT_SUCCESS;
}
