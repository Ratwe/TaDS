#include "combinatorics.h"
#include "utils.h"

int main()
{
    int ec;
    int size;
    adjmat_t *result;

    welcome();

    printf("Введите число вершин графа: ");
    ec = rnginput(&size, 1, INT_MAX);
    if (ec)
    {
        printf("Введено недопустимое значение! Повторите попытку.\n");
        return ec;
    }

    adjmat_t *matrix = amcreate(size);
    printf("Введите рёбра графа в формате 'V1 V2' (нумерация вершин начинается с 0).\n"
           "Для завершения ввода введите '-1' :\n");
    ec = amfill(matrix);
    if (ec)
    {
        if (ec == EINVALIDINTEGER || ec == EINVALIDRANGE)
        {
            printf("Введено недопустимое значение! Повторите попытку.\n");
            amfree(matrix);
            return ec;
        }
        if (ec == EINVALIDVERTEXPAIR)
        {
            printf("%s\n", "Путь в себя невозможен!");
            amfree(matrix);
            return ec;
        }
    }

    uint64_t start, end, time, temp = 0;
    start = tick();
    while (temp++ < 1000)
        result = cutgraph(*matrix);
    end = tick();
    time = end - start;

    if (result)
    {
        printf("Удаленные рёбра графа отмечены красным цветом.\n");
        gvexport(*matrix, *result);
        printf("Время выполнения алгоритма: %ju\n", time);
        amfree(matrix);
        amfree(result);
        return EOK;
    }
    printf("Невозможно сделать граф несвязным!\n");
    amfree(matrix);
    amfree(result);

    return EOK;
}
