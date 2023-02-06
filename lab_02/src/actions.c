#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#include "defines.h"
#include "country.h"
#include "menu.h"

int scan_country(char *fields[TABLE_FIELDS_COUNT], FILE *f)
{
    int rc = fscanf(f, "%s %s %s %s %s %s %s %s %s %s", \
        fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], \
        fields[6], fields[7], fields[8], fields[9]);

    if (rc == EOF)
        return EOF;

    if (rc != TABLE_FIELDS_COUNT)
    {
        LOG_DEBUG("[DB]: rc = %d\n", rc);
        return TABLE_FIELDS_COUNT_ERR;
    }

    return EXIT_SUCCESS;
}

void print_country(country_t country)
{
    printf("|------------|------------|-----------------|---------------|-----|------------|------------|------------|-----------|-----------|\n");

    // LOG_DEBUG("[DB]: cur_country = ");

    printf("|%-12s|%-12d|%-17s|", country.name, country.people, country.capital);

    printf("%-15s|", country.mainland);

    printf("%-5d|%-12s|", country.pcr, country.type);

    if (!strcmp(country.type, "Excursion"))
        printf("%-12d|%-12s|%-11s|%-11s|\n", \
            country.info.excursion.obj_count, country.info.excursion.type, "", "");

    else if (!strcmp(country.type, "Beach"))
        printf("%-12s|%-12d|%-11d|%-11d|\n",  country.info.beach.season, \
            country.info.beach.temp_air, country.info.beach.temp_water, country.info.beach.arriving_time);

    else if (!strcmp(country.type, "Sport"))
        printf("%-12s|%-12d|%-11s|%-11s|\n", \
            country.info.sport.type, country.info.sport.cost, "", "");
}

int load_table(country_table_t *table, char *filename)
{
    int error_code;

    if ((error_code = check_open_file(filename)))
        return error_code;

    FILE *f = fopen(filename, "r");
    char *fields[TABLE_FIELDS_COUNT];

    LOG_DEBUG("[DB]: len = %ld\n", table->len);

    for (int i = 0; i < TABLE_FIELDS_COUNT; i++)
    {
        fields[i] = calloc(MAX_CAPITAL_LEN, sizeof(char));

        if (fields[i] == NULL)
            return ALLOC_MEM_ERR;
    }


    LOG_DEBUG("[DB]: load_table file opened\n");

    int rc = scan_country(fields, f);  // названия столбцов
    rc = scan_country(fields, f);  // первая страна

    while (rc == EXIT_SUCCESS)
    {
        LOG_DEBUG("------------------------\n");
        print_fields;

        if (strlen(fields[0]) > MAX_NAME_LEN)
        {
            free_fields;
            fclose(f);
            return NAME_LEN_ERR;
        }

        strcpy(cur_country.name, fields[0]);

        if (!strtol(fields[1], NULL, 10))
        {
            free_fields;
            fclose(f);
            LOG_DEBUG("[DB]: strol1: %ld\n", strtol(fields[1], NULL, 10));
            return NOT_INT_ERR;
        }

        LOG_DEBUG("[DB]: people passed\n");

        cur_country.people = strtol(fields[1], NULL, 10);

        if (strlen(fields[2]) > MAX_CAPITAL_LEN)
        {
            free_fields;
            fclose(f);
            return CAPITAL_LEN_ERR;
        }

        strcpy(cur_country.capital, fields[2]);

        if (strlen(fields[3]) > MAX_MAINLAND_LEN)
        {
            free_fields;
            fclose(f);
            return MAINLAND_LEN_ERR;
        }

        strcpy(cur_country.mainland, fields[3]);

        errno = 0;

        strtol(fields[4], NULL, 10);

        if (errno)
        {
            free_fields;
            fclose(f);
            LOG_DEBUG("[DB]: strol4: %ld\n", strtol(fields[4], NULL, 10));
            return NOT_INT_ERR;
        }

        LOG_DEBUG("[DB]: PCR passed\n");

        cur_country.pcr = strtol(fields[4], NULL, 10);

#ifdef DEBUG
print_country(cur_country);
#endif

        if (strlen(fields[5]) > MAX_TYPE_LEN)
        {
            free_fields;
            fclose(f);
            return TYPE_LEN_ERR;
        }

        strcpy(cur_country.type, fields[5]);

        if (!strcmp(fields[5], "Excursion"))
        {
            LOG_DEBUG("[DB] EXC info started\n");

            errno = 0;

            strtol(fields[6], NULL, 10);

            if (errno)
            {
                free_fields;
                fclose(f);
                LOG_DEBUG("[DB]: strol6: %ld\n", strtol(fields[6], NULL, 10));
                return NOT_INT_ERR;
            }

            LOG_DEBUG("[DB]: EXC obj_count passed\n");

            cur_country.info.excursion.obj_count = strtol(fields[6], NULL, 10);
            strcpy(cur_country.info.excursion.type, fields[7]);
        }
        else if (!strcmp(fields[5], "Beach"))
        {
            LOG_DEBUG("[DB]: BEACH info started\n");

            strcpy(cur_country.info.beach.season, fields[6]);
            LOG_DEBUG("[DB]: fields[6] = %s\n", fields[6]);
            LOG_DEBUG("[DB]: season = %s\n", cur_country.info.beach.season);

            errno = 0;
            cur_country.info.beach.temp_air = strtol(fields[7], NULL, 10);

            if (errno)
            {
                free_fields;
                return NOT_INT_ERR;
            }

            errno = 0;
            cur_country.info.beach.temp_water = strtol(fields[8], NULL, 10);

            if (errno)
            {
                free_fields;
                return NOT_INT_ERR;
            }

            errno = 0;
            cur_country.info.beach.arriving_time = strtol(fields[9], NULL, 10);

            if (errno)
            {
                free_fields;
                return NOT_INT_ERR;
            }
        }
        else if (!strcmp(fields[5], "Sport"))
        {
            LOG_DEBUG("[DB] SPORT info started\n");

            strcpy(cur_country.info.sport.type, fields[6]);

            errno = 0;
            cur_country.info.sport.cost = strtol(fields[7], NULL, 10);

            if (errno)
            {
                free_fields;
                return NOT_INT_ERR;
            }
        }
        else
        {
            free_fields;
            fclose(f);
            return INCORRECT_TYPE_ERROR;
        }

        print_country(cur_country);
        table->len++;
        rc = scan_country(fields, f);
    }

    free_fields;
    fclose(f);

    if (rc != EOF)
        return TABLE_FIELDS_COUNT_ERR;

    return EXIT_SUCCESS;
}

void print_table(country_table_t table)
{
    printf("|%-12s|%-12s|%-17s|%-15s|%-5s|%-12s|%-12s|%-12s|%-11s|%-11s|\n", \
        "Name", "People", "Capital", "Mainland", "PCR", "Type", "Optional1", \
        "Optional2", "Optional3", "Optional4");

    for (size_t i = 0; i < table.len; i++)
        print_country(table.country[i]);
}

int add_country(country_table_t *table)
{
    char *fields[TABLE_FIELDS_COUNT];

    for (int i = 0; i < TABLE_FIELDS_COUNT; i++)
    {
        fields[i] = calloc(MAX_CAPITAL_LEN, sizeof(char));

        if (fields[i] == NULL)
            return ALLOC_MEM_ERR;
    }

#ifdef DEBUG
print_country(cur_country);
#endif

    printf("Введите название страны: ");
    scanf("%s", fields[0]);

    if (strlen(fields[0]) > MAX_NAME_LEN)
        return NAME_LEN_ERR;

    printf("Введите население страны (число): ");
    scanf("%s", fields[1]);

    if (!strtol(fields[1], NULL, 10))
        return NOT_INT_ERR;

    printf("Введите название столицы: ");
    scanf("%s", fields[2]);

    if (strlen(fields[2]) > MAX_CAPITAL_LEN)
        return CAPITAL_LEN_ERR;

    printf("Введите название материка страны (Asia, NorthAmerica, Oceania, etc): ");
    scanf("%s", fields[3]);

    if (strlen(fields[3]) > MAX_MAINLAND_LEN)
        return MAINLAND_LEN_ERR;

    printf("Нужен ли для поездки ПЦР-тест (1 - нужен, 0 - не нужен): ");
    scanf("%s", fields[4]);

    errno = 0;

    strtol(fields[4], NULL, 10);

    if (errno)
        return NOT_INT_ERR;


    printf("Введите тип отдыха в стране (Excursion, Beach, Sport): ");
    scanf("%s", fields[5]);

    if (strcmp(fields[5], "Excursion") && strcmp(fields[5], "Beach") && strcmp(fields[5], "Sport"))
        return INCORRECT_TYPE_ERROR;

    if (strlen(fields[5]) > MAX_TYPE_LEN)
        return TYPE_LEN_ERR;

    strcpy(cur_country.name, fields[0]);
    cur_country.people = strtol(fields[1], NULL, 10);
    strcpy(cur_country.capital, fields[2]);
    strcpy(cur_country.mainland, fields[3]);
    cur_country.pcr = strtol(fields[4], NULL, 10);
    strcpy(cur_country.type, fields[5]);

    if (!strcmp(fields[5], "Excursion"))
    {
        printf("Введите кол-во объектов для посещения (число): ");
        scanf("%s", fields[6]);

        if (!strtol(fields[6], NULL, 10))
            return NOT_INT_ERR;

        printf("Введите тип этих объектов (History, Art, Nature): ");
        scanf("%s", fields[7]);

        if (strcmp(fields[7], "History") && strcmp(fields[7], "Art") && strcmp(fields[7], "Nature"))
            return INCORRECT_TYPE_ERROR;

        cur_country.info.excursion.obj_count = strtol(fields[6], NULL, 10);
        strcpy(cur_country.info.excursion.type, fields[7]);
    }

    else if (!strcmp(fields[5], "Beach"))
    {
        printf("Введите основной сезон (Winter, Spring, Summer, Autumn): ");
        scanf("%s", fields[6]);

        if (strcmp(fields[6], "Winter") && strcmp(fields[6], "Spring") \
            && strcmp(fields[6], "Summer") && strcmp(fields[6], "Autumn"))
            return INCORRECT_TYPE_ERROR;

        errno = 0;

        printf("Введите температуру воздуха (число): ");
        scanf("%s", fields[7]);

        strtol(fields[7], NULL, 10);

        if (errno)
            return NOT_INT_ERR;

        printf("Введите температуру воды (число): ");
        scanf("%s", fields[8]);

        strtol(fields[8], NULL, 10);

        if (errno)
            return NOT_INT_ERR;

        printf("Введите время полёта (в минутах): ");
        scanf("%s", fields[9]);

        if (!strtol(fields[9], NULL, 10))
            return NOT_INT_ERR;

        strcpy(cur_country.info.beach.season, fields[6]);
        cur_country.info.beach.temp_air = strtol(fields[7], NULL, 10);
        cur_country.info.beach.temp_water = strtol(fields[8], NULL, 10);
        cur_country.info.beach.arriving_time = strtol(fields[9], NULL, 10);

    }
    else if (!strcmp(fields[5], "Sport"))
    {
        printf("Введите основной вид спорта (Skiing, Surfing, Climb): ");
        scanf("%s", fields[6]);

        if (strcmp(fields[6], "Skiing") && strcmp(fields[6], "Surfing") && strcmp(fields[6], "Climb"))
            return INCORRECT_TYPE_ERROR;

        errno = 0;

        printf("Введите стоимость (в местной валюте): ");
        scanf("%s", fields[7]);

        if (!strtol(fields[7], NULL, 10))
            return NOT_INT_ERR;

        LOG_DEBUG("[DB]: cur_country.info.sport.type = %s\n", cur_country.info.sport.type);
        strcpy(cur_country.info.sport.type, fields[6]);
        LOG_DEBUG("[DB]: cur_country.info.sport.type = %s\n", cur_country.info.sport.type);
        LOG_DEBUG("[DB]: fields[6] = %s\n", fields[6]);
        LOG_DEBUG("[DB]: *fields[6] = %d\n", *fields[6]);

        cur_country.info.sport.cost = strtol(fields[7], NULL, 10);
    }
    else
        return INCORRECT_TYPE_ERROR;

#ifdef DEBUG
print_country(cur_country);
#endif

    table->len++;
    LOG_DEBUG("[DB]: EXIT_SUCCESS\n");

    return EXIT_SUCCESS;
}

int delete_country(country_table_t *table)
{
    char name[MAX_NAME_LEN];

    printf("Введите название страны: ");
    scanf("%s", name);

    for (size_t i = 0; i < table->len; i++)
        if (!strcmp(table->country[i].name, name))
        {
            while (i++ < table->len)
                table->country[i - 1] = table->country[i];

            table->len--;

            return EXIT_SUCCESS;
        }

    return NO_MATCH_COUNTRY;
}

void update_key_table(country_table_t table, country_key_table_t *key_table)
{
    key_table->len = table.len;

    for (size_t i = 0; i < table.len; i++)
    {
        strcpy(key_table->key[i].name, table.country[i].name);
        key_table->key[i].index = i;
    }
}

void bubble_sort_key_table(country_key_table_t *key_table)
{
    struct timeval ta, te;

    int count = 0;

    gettimeofday(&ta, NULL);

    while (count++ < 1000)
    {

        for (size_t i = 0; i < key_table->len; i++)
            for (size_t j = 1; j < key_table->len; j++)
                if (strcmp(key_table->key[j - 1].name, key_table->key[j].name) > 0)
                {
                    country_key_t temp = key_table->key[j];
                    key_table->key[j] = key_table->key[j - 1];
                    key_table->key[j - 1] = temp;
                }

    }

    gettimeofday(&te, NULL);

    LOG_DEBUG("[TIME]: bubble_sort_key_table = %lf\n", te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec) / 1000000000.0);
}

int compare_key(const void *key1, const void *key2)
{
    country_key_t *a = (country_key_t *)key1;
    country_key_t *b = (country_key_t *)key2;

    char *name1 = a->name;
    char *name2 = b->name;

    return strcmp(name1, name2);
}

void qsort_key_table(country_key_table_t *key_table)
{
    struct timeval ta, te;

    int count = 0;

    gettimeofday(&ta, NULL);

    while (count++ < 1000)
        qsort(key_table->key, key_table->len, sizeof(country_key_t), compare_key);

    gettimeofday(&te, NULL);

    LOG_DEBUG("[TIME]: qsort_key_table = %lf\n", te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec) / 1000000000.0);
}

void bubble_sort_table(country_table_t *table)
{
    struct timeval ta, te;

    int count = 0;

    gettimeofday(&ta, NULL);

    while (count++ < 1000)
    {

        for (size_t i = 0; i < table->len; i++)
            for (size_t j = 1; j < table->len; j++)
                if (strcmp(table->country[j - 1].name, table->country[j].name) > 0)
                {
                    country_t temp = table->country[j];
                    table->country[j] = table->country[j - 1];
                    table->country[j - 1] = temp;
                }
    }

    gettimeofday(&te, NULL);

    LOG_DEBUG("[TIME]: bubble_sort_table = %lf\n", te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec) / 1000000000.0);
}

int compare_country(const void *country1, const void *country2)
{
    country_t *a = (country_t *)country1;
    country_t *b = (country_t *)country2;

    char *name1 = a->name;
    char *name2 = b->name;

    return strcmp(name1, name2);
}

void qsort_table(country_table_t *table)
{
    struct timeval ta, te;

    int count = 0;

    gettimeofday(&ta, NULL);

    while(count++ < 1000)
        qsort(table->country, table->len, sizeof(country_t), compare_country);

    gettimeofday(&te, NULL);

    LOG_DEBUG("[TIME]: qsort_table = %lf\n", te.tv_sec - ta.tv_sec + (te.tv_usec - ta.tv_usec) / 1000000000.0);
}

void print_key(country_key_t key)
{
    char str[9];
    sprintf(str, "%d", key.index);

    LOG_DEBUG("[DB]: cur_key = ");

    printf("|%-12s|%-9s|\n", key.name, str);
}

void print_key_table(country_key_table_t key_table)
{
    printf("|%-12s|%-9s|\n", "Name", "Table Num");

    for (size_t i = 0; i < key_table.len; i++)
        print_key(key_table.key[i]);
}

void print_table_through_keys(country_table_t table, country_key_table_t key_table)
{
    printf("|%-12s|%-12s|%-17s|%-15s|%-5s|%-12s|%-12s|%-12s|%-11s|%-11s|\n", \
        "Name", "People", "Capital", "Mainland", "PCR", "Type", "Optional1", \
        "Optional2", "Optional3", "Optional4");

    for (size_t i = 0; i < key_table.len; i++)
            print_country(table.country[key_table.key[i].index]);
}

int search_country(country_table_t table)
{
    char mainland[MAX_MAINLAND_LEN];
    char sport_type[MAX_TYPE_LEN];
    int error_code = NO_MATCH_COUNTRY;

    printf("Введите материк (Asia, NorthAmerica, Oceania, etc): ");

    if (!scanf("%s", mainland))
        return MAINLAND_LEN_ERR;

    printf("Введите вид спорта (Skiing, Surfing, Climb): ");

    if (!scanf("%s", sport_type))
        return TYPE_LEN_ERR;

    if (strcmp(sport_type, "Skiing") && strcmp(sport_type, "Surfing") && strcmp(sport_type, "Climb"))
        return INCORRECT_TYPE_ERROR;

    printf("Поиск подходящих стран...\n");

    for (size_t i = 0; i < table.len; i++)
    {
        country_t country = table.country[i];

        if (!strcmp(country.mainland, mainland))
            if (!strcmp(country.type, "Sport"))
                if (!strcmp(country.info.sport.type, sport_type))
                {
                    print_country(country);
                    error_code = EXIT_SUCCESS;
                }
    }

    return error_code;
}
