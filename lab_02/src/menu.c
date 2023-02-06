#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "menu.h"
#include "defines.h"
#include "country.h"
#include "actions.h"

int check_open_file(char *filename)
{
    struct stat buffer;
    int exist = stat(filename, &buffer);

    if (exist == 0)
        return EXIT_SUCCESS;
    else
        return OPEN_FILE_ERR;
}

int print_error(int error_code)
{
    switch (error_code)
    {
        case OPEN_FILE_ERR:
            LOG_ERR("Не удалось открыть файл!\n")
            break;

        case ARGC_COUNT_ERR:
            LOG_ERR("Неверные аргументы командной строки.\n")
            break;

        case MENU_OPTION_ERR:
            LOG_ERR("Введён некорректный пункт меню.\n")
            break;

        case TYPE_LEN_ERR:
            LOG_ERR("Превышена длина вводимого типа!\n");
            break;

        case SEASON_ERR:
            LOG_ERR("Неправильный сезон!\n");
            break;

        case NAME_LEN_ERR:
            LOG_ERR("Превышена длина названия страны.\n");
            break;

        case TABLE_LEN_ERR:
            LOG_ERR("Превышена длина списка!\n");
            break;

        case TABLE_FIELDS_COUNT_ERR:
            LOG_ERR("Неверное количество полей!\n");
            break;

        case INCORRECT_TYPE_ERROR:
            LOG_ERR("Введён некорректный тип!\n");
            break;

        case NOT_INT_ERR:
            LOG_ERR("Требуется целое число!\n");
            break;

        case ALLOC_MEM_ERR:
            LOG_ERR("Ошибка выделения памяти!\n");
            break;

        case NO_MATCH_COUNTRY:
            LOG_ERR("Подходящей страны не найдено!\n")
            break;
    }

    return error_code;
}

void print_menu()
{
    printf("\n");
    printf("          МЕНЮ\n\n");
    printf("1  - Загрузить таблицу стран из файла\n");
    printf("2  - Просмотреть текущую таблицу\n");
    printf("3  - Добавить информацию о новой стране в конец таблицы\n");
    printf("4  - Удалить страну из списка по названию\n");
    printf("5  - Просмотреть отсортированную по названию страны таблицу ключей\n");
    printf("6  - Просмотр упорядоченной по названию страны таблицы\n");
    printf("7  - Просмотр таблицы в упорядоченном по названию страны виде\n");
    printf("     по упорядоченной таблице ключей\n");
    printf("8 - Вывод списка стран на выбранном материке, где можно заняться указанным видом спорта\n");
    printf("0  - Выход\n");
    printf("\n");
}

int choose_action(int *action)
{
    printf("Введите пункт меню: ");

    int rc = scanf("%d", action);

    LOG_DEBUG("[DB]: rc = %d", rc);

    if (rc != 1 || *action < 0 || *action > 10)
        return MENU_OPTION_ERR;

    return EXIT_SUCCESS;
}

int do_action(int action, char *filename, country_table_t *table, country_key_table_t *key_table)
{
    int error_code = EXIT_SUCCESS;

    LOG_DEBUG("[DB]: action = %d\n", action);

    switch (action)
    {
        case 1:
            if ((error_code = load_table(table, filename)))
                return error_code;

            printf("Список из файла успешно загружен!\n");

            LOG_DEBUG("[DB]: table->len = %ld\n", table->len);

            break;

        case 2:
            printf("Текущая таблица:\n");

            LOG_DEBUG("[DB]: table->len = %ld\n", table->len);

            print_table(*table);

            break;

        case 3:
            if ((error_code = add_country(table)))
                return error_code;

            break;

        case 4:
            if ((error_code = delete_country(table)))
                printf("Страны с таким названием в списки нет!\n");
            else
                printf("Запись страны успешно удалена!");

            break;

        case 5:
            printf("Обновление таблицы ключей...\n");

            update_key_table(*table, key_table);

#ifdef DEBUG
printf("[DB]: key_table = \n");
print_key_table(*key_table);
#endif

            // bubble_sort_key_table(key_table);
            qsort_key_table(key_table);

            printf("Отсортированная таблица ключей: \n");
            print_key_table(*key_table);

            break;

        case 6:
            printf("Упорядоченная таблица: \n");

            bubble_sort_table(table);
            // qsort_table(table);

            print_table(*table);

            break;

        case 7:
            printf("Обновление таблицы ключей...\n");

            update_key_table(*table, key_table);

            printf("Упорядоченная таблица по таблице ключей: \n");

            // bubble_sort_key_table(key_table);
            qsort_key_table(key_table);

            print_table_through_keys(*table, *key_table);

            break;

        case 8:
            if ((error_code = search_country(*table)))
                return error_code;

            break;

        default:
            printf("Программа успешно завершена.\n");

            return error_code;

            break;
    }

    return EXIT_SUCCESS;
}
