/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to get header cpu data.
*/

#include "./../../include/my_top.h"

void cpu_calcul(main_t *main)
{
    float total = 0;
    main->info.header_cpu.us = main->info.header_cpu_new[0] - main->info.header_cpu_old[0];
    main->info.header_cpu.sy = main->info.header_cpu_new[1] - main->info.header_cpu_old[1];
    main->info.header_cpu.ni = main->info.header_cpu_new[2] - main->info.header_cpu_old[2];
    main->info.header_cpu.id = main->info.header_cpu_new[3] - main->info.header_cpu_old[3];
    main->info.header_cpu.wa = main->info.header_cpu_new[4] - main->info.header_cpu_old[4];
    main->info.header_cpu.hi = main->info.header_cpu_new[5] - main->info.header_cpu_old[5];
    main->info.header_cpu.si = main->info.header_cpu_new[6] - main->info.header_cpu_old[6];
    main->info.header_cpu.st = main->info.header_cpu_new[7] - main->info.header_cpu_old[7];
    total = main->info.header_cpu.us + main->info.header_cpu.sy + main->info.header_cpu.ni +
        main->info.header_cpu.id + main->info.header_cpu.wa + main->info.header_cpu.hi +
        main->info.header_cpu.si + main->info.header_cpu.st;
    main->info.header_cpu.us = (main->info.header_cpu.us / total) * 100;
    main->info.header_cpu.sy = (main->info.header_cpu.sy / total) * 100;
    main->info.header_cpu.ni = (main->info.header_cpu.ni / total) * 100;
    main->info.header_cpu.id = (main->info.header_cpu.id / total) * 100;
    main->info.header_cpu.wa = (main->info.header_cpu.wa / total) * 100;
    main->info.header_cpu.hi = (main->info.header_cpu.hi / total) * 100;
    main->info.header_cpu.si = (main->info.header_cpu.si / total) * 100;
    main->info.header_cpu.st = (main->info.header_cpu.st / total) * 100;
}

static char *stock_cpu_data(char *str, int *dlen, char buf[16])
{
    int len = 0;

    while (str[*dlen] != ' ')
        (*dlen)++;
    while (str[*dlen] == ' ')
        (*dlen)++;
    while (str[*dlen] != ' ' && str[*dlen] != '\n') {
        buf[len] = str[*dlen];
        (*dlen)++;
        len++;
    }
    buf[len] = '\0';
    return buf;
}

static float parsing_str_cpu(char *str, int *len)
{
    int n = 0;
    float f = 0;
    char buf[16];

    if (str != NULL)
        n = atoi(stock_cpu_data(str, len, buf));
    f = (float)n;
    return f;
}

static void range_cpu(char *buf, main_t *main)
{
    int len = 0;

    for (int i = 0; i < 10; i++) {
        main->info.header_cpu_old[i] = main->info.header_cpu_new[i];
        main->info.header_cpu_new[i] = parsing_str_cpu(buf, &len);
    }
}

int cpu_function(main_t *main)
{
    FILE *file;
    char buf[1000];

    file = fopen(PATH_TASKS, "r");
    if (file == NULL)
        return EXIT_FAIL;
    fread(buf, sizeof(char), sizeof(buf), file);
    range_cpu(buf, main);
    fclose(file);
    return EXIT_SUCC;
}