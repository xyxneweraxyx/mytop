/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to get header tasks data.
*/

#include "./../../include/my_top.h"

static char *stock_tasks_data(char *str, char buf[16])
{
    int i = 0;
    int len = 0;

    while (str[i] != ' ')
        i++;
    while (str[i] == ' ')
        i++;
    while (str[i] != '\n') {
        buf[len] = str[i];
        i++;
        len++;
    }
    buf[len] = '\0';
    return buf;
}

static int parsing_str_tasks(char *str)
{
    int n = 0;
    char buf[16] = {0};

    if (str != NULL)
        n = atoi(stock_tasks_data(str, buf));
    return n;
}

static void range_tasks(char *buf, main_t *main)
{
    char *str;

    str = strstr(buf, "processes");
    //printw("%d\n", parsing_str_tasks(str));
    main->info.header_tasks.total = parsing_str_tasks(str) / 1000;
    str = strstr(buf, "procs_running");
    main->info.header_tasks.running = parsing_str_tasks(str);
    main->info.header_tasks.sleeping = main->info.header_tasks.total - main->info.header_tasks.running;
    str = strstr(buf, "procs_blocked");
    main->info.header_tasks.stopped = parsing_str_tasks(str);
    main->info.header_tasks.zombie = 0.0;
}

int fetch_header_tasks(main_t *main)
{
    FILE *file;
    char buf[6000];

    file = fopen(PATH_TASKS, "r");
    if (file == NULL)
        return 84;
    fread(buf, sizeof(char), sizeof(buf), file);
    range_tasks(buf, main);
    fclose(file);
    return 0;
}