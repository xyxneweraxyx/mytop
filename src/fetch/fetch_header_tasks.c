/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to get header tasks data.
*/

#include "./../../include/my_top.h"

static void range_tasks(char *buf, main_t *main)
{
    int i = 0;

    while (buf[i] && buf[i] != ')')
        i++;
    if (!buf[i])
        return;
    i += 2;
    if (buf[i] == 'S' || buf[i] == 'D' || buf[i] == 'I')
        main->info.header_tasks.sleeping++;
    if (buf[i] == 'R')
        main->info.header_tasks.running++;
    if (buf[i] == 'T' || buf[i] == 't')
        main->info.header_tasks.stopped++;
    if (buf[i] == 'Z')
        main->info.header_tasks.zombie++;
}

static void init_task_counters(main_t *main)
{
    main->info.header_tasks.running = 0;
    main->info.header_tasks.sleeping = 0;
    main->info.header_tasks.stopped = 0;
    main->info.header_tasks.zombie = 0;
    main->info.header_tasks.total = 0;
}

static void calc_total_tasks(main_t *main)
{
    main->info.header_tasks.total = main->info.header_tasks.running +
        main->info.header_tasks.sleeping + main->info.header_tasks.stopped +
        main->info.header_tasks.zombie;
}

static void process_task_loop(DIR *d, main_t *main)
{
    char buf[512];
    char path[32];
    FILE *file = NULL;
    struct dirent *rep = NULL;

    while (1) {
        rep = readdir(d);
        if (!rep)
            break;
        if (atoi(rep->d_name) == 0)
            continue;
        sprintf(path, "/proc/%s/stat", rep->d_name);
        file = fopen(path, "r");
        if (!file)
            continue;
        fread(buf, 1, sizeof(buf), file);
        fclose(file);
        range_tasks(buf, main);
    }
}

int fetch_header_tasks(main_t *main)
{
    DIR *d = opendir("/proc");

    if (!d)
        return EXIT_FAIL;
    init_task_counters(main);
    process_task_loop(d, main);
    calc_total_tasks(main);
    closedir(d);
    return EXIT_SUCC;
}