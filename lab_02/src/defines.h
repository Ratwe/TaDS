#ifndef __DEFINES__H__
#define __DEFINES__H__

#define EXIT_SUCCESS 0
#define ARGC_COUNT 2
#define TABLE_FIELDS_COUNT 10
// ---------------------
#define MAX_TYPE_LEN 10
#define SEASON_LEN 6
#define MAX_NAME_LEN 10
#define MAX_CAPITAL_LEN 15
#define MAX_MAINLAND_LEN 13
#define MAX_TABLE_LEN 10000
// ---------------------

#define OPEN_FILE_ERR 101
#define ARGC_COUNT_ERR 102
#define MENU_OPTION_ERR 103
#define TYPE_LEN_ERR 104
#define SEASON_ERR 105
#define NAME_LEN_ERR 106
#define CAPITAL_LEN_ERR 107
#define MAINLAND_LEN_ERR 108
#define TABLE_LEN_ERR 109
#define TABLE_FIELDS_COUNT_ERR 110
#define INCORRECT_TYPE_ERROR 111
#define NOT_INT_ERR 112
#define ALLOC_MEM_ERR 113
#define NO_MATCH_COUNTRY 114

#endif

#ifdef DEBUG
#define LOG_DEBUG(...) { printf(__VA_ARGS__); }
#else
#define LOG_DEBUG(...) {}
#endif

#define LOG_ERR(...) { printf("Ошибка: "__VA_ARGS__); }

#define cur_country table->country[table->len]

#define print_fields do { \
    for (int i = 0; i < TABLE_FIELDS_COUNT; i ++) \
        printf("%s ", fields[i]); \
    printf("\n"); \
} while (0);

#define free_fields \
    for (int i = 0; i < TABLE_FIELDS_COUNT; i ++) \
        free(fields[i]);
