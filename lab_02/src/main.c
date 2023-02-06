#include <stdio.h>

#include "menu.h"
#include "defines.h"

int check_args(int argc, char **argv)
{
    int error_code;

    if (argc != ARGC_COUNT)
        return ARGC_COUNT_ERR;

    if ((error_code = check_open_file(argv[1])))
        return error_code;

    return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{

    int error_code = EXIT_SUCCESS;
    country_table_t country_table = { 0 };
    country_key_table_t country_key_table = { 0 };

    if ((error_code = check_args(argc, argv)))
        return print_error(error_code);

    printf("-----------------------------------------------------------\n");
    printf("              Программа обработки списка стран\n");
    printf("-----------------------------------------------------------\n");

    int action = 1;

    while (action)
    {
        print_menu();

        if ((error_code = choose_action(&action)))
            return print_error(error_code);

        if ((error_code = do_action(action, argv[1], &country_table, &country_key_table)))
            return print_error(error_code);
    }

    return error_code;
}
