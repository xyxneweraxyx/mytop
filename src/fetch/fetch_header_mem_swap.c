/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to get header cpu data.
*/

#include "./../../include/my_top.h"

char *stock_mem_data(char *str, char buf[16])
{
    int i = 0;
    int len = 0;
    while (str[i] != ':')
        i++;
    i++;
    while (str[i] == ' ')
        i++;
    while (str[i] != ' ') {
        buf[len] = str[i];
        i++;
        len++;
    }
    buf[len] = '\0';
    return buf;
}

float parsing_str_mem(char *str)
{
    int n = 0;
    float f;
    char buf[16];

    if (str != NULL)
        n = atoi(stock_mem_data(str, buf));
    f = (float)n;
    return f;
}

void range_mem(char *buf, main_t *main)
{
    char *str;


    str = strstr(buf, "MemTotal");
    main->info.header_mem.total = parsing_str_mem(str) / 1024;
    str = strstr(buf, "MemFree");
    main->info.header_mem.free = parsing_str_mem(str) / 1024;
    str = strstr(buf, "Cached");
    main->info.header_mem.cache = parsing_str_mem(str) / 1024;
    str = strstr(buf, "SwapTotal");
    main->info.header_swap.total = parsing_str_mem(str) / 1024;
    str = strstr(buf, "SwapFree");
    main->info.header_swap.free = parsing_str_mem(str) / 1024;
    str = strstr(buf, "MemAvailable");
    main->info.header_swap.avail = parsing_str_mem(str) / 1024;
    main->info.header_mem.used = main->info.header_mem.total - main->info.header_mem.free;
    main->info.header_swap.used = main->info.header_swap.total - main->info.header_swap.free;
}

int fetch_header_mem_swap(main_t *main)
{
    FILE *file;
    char buf[5000];

    file = fopen(PATH_MEMINFO, "r");
    if (file == NULL)
        return EXIT_FAIL;
    fread(buf, sizeof(char), sizeof(buf), file);
    range_mem(buf, main);
    fclose(file);
    return EXIT_SUCC;
}