/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to initialize structure.
*/

#include "./../include/my_top.h"

static void modify_time(char *time)
{
    time[1] += 1;
    if (time[0] == '2' && time[1] == '4') {
        time[0] = '0';
        time[1] = '0';
    }
    if (time[1] == '9' + 1) {
        time[1] = '0';
        time[0] += 1;
    }
}

int fetch_header(main_t *main)
{
    buff_from_path(main->info.header_top.cur_time, 11, 18, PATH_CUR_TIME);
    modify_time(main->info.header_top.cur_time);
    buff_from_path(main->info.header_top.load_avg, 0, 13, PATH_LOADAVG);
    return EXIT_SUCC;
}

int fetch(main_t *main)
{
    if (fetch_header(main) == EXIT_FAIL)
        return EXIT_FAIL;
    return EXIT_SUCC;
}
