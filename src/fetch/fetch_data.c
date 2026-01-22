/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to initialize structure.
*/

#include "./../../include/my_top.h"

int fetch(main_t *main)
{
    if (fetch_header_top(main) == EXIT_FAIL)
        return EXIT_FAIL;
    if (fetch_header_tasks(main) == EXIT_FAIL)
        return EXIT_FAIL;
    if (fetch_header_mem_swap(main) == EXIT_FAIL)
        return EXIT_FAIL;
    if (fetch_processes(main) == EXIT_FAIL)
        return EXIT_FAIL;
    return EXIT_SUCC;
}
