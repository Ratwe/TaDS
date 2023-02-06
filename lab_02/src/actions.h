#ifndef __ACTIONS__H__
#define __ACTIONS__H__

int load_table(country_table_t *table, char *filename);

void print_table(country_table_t table);

void print_key_table(country_key_table_t key_table);

int add_country(country_table_t *table);

int delete_country(country_table_t *table);

void update_key_table(country_table_t table, country_key_table_t *key_table);

void bubble_sort_key_table(country_key_table_t *key_table);

void bubble_sort_table(country_table_t *table);

void print_table_through_keys(country_table_t table, country_key_table_t key_table);

void qsort_key_table(country_key_table_t *key_table);

void qsort_table(country_table_t *table);

int search_country(country_table_t table);

#endif
