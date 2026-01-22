/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to get header tasks data.
*/

#include "./../../include/my_top.h"

void range_tasks(char *buf, main_t *main)
{
    int i = 0;

    while (buf[i] != ')')
        i++;
    i += 2;
    if (buf[i] == 'S' || buf[i] == 'D' || buf[i] == 'I')
        main->info.header_tasks.sleeping++;
    if (buf[i] == 'R')
        main->info.header_tasks.running++;
    if (buf[i] == 'T')
        main->info.header_tasks.stopped++;
    if (buf[i] == 'Z')
        main->info.header_tasks.zombie++;
    main->info.header_tasks.total = main->info.header_tasks.running +
        main->info.header_tasks.sleeping + main->info.header_tasks.stopped +
        main->info.header_tasks.zombie;
}

int fetch_header_tasks(main_t *main)
{
    char buf[5000];
    FILE *file;
    DIR *d = opendir("/proc");
    struct dirent *rep = readdir(d);

    main->info.header_tasks.running = 0;
    main->info.header_tasks.sleeping = 0;
    main->info.header_tasks.stopped = 0;
    main->info.header_tasks.zombie = 0;
    main->info.header_tasks.total = 0;
    while (rep != NULL) {
        if (atoi(rep->d_name) != 0) {
            sprintf(buf, "../../../../proc/%s/stat", rep->d_name);
            file = fopen(buf, "r");
            fread(buf, sizeof(char), sizeof(buf), file);
            fclose(file);
            range_tasks(buf, main);
        }
        rep = readdir(d);
    }
    closedir(d);
    return EXIT_SUCC;
}