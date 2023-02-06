#ifndef __MENU__H__
#define __MENU__H__

#include "country.h"

int check_open_file(char *filename);

int print_error(int error_code);

void print_menu();

int choose_action(int *action);

int do_action(int action, char *filename, country_table_t *table, country_key_table_t *key_table);

#endif
