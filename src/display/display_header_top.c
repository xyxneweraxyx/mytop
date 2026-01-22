/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../../include/my_top.h"

static void fill_time(char ut[30], int t)
{
    if (t >= 86400 * 2) {
        if (t % 86400 >= 3600)
            sprintf(ut, "%d days, %02d:%02d", t / 86400, (t % 86400) / 3600, (t % 3600) / 60);
        else
            sprintf(ut, "%d days, %02d min", t / 86400, (t % 3600) / 60);
    }
    if (t >= 86400 && t < 86400 * 2) {
        if (t % 86400 >= 3600)
            sprintf(ut, "%d day, %02d:%02d", t / 86400, (t % 86400) / 3600, (t % 3600) / 60);
        else
            sprintf(ut, "%d day, %02d min", t / 86400, (t % 3600) / 60);
    }
    if (t >= 3600 && t < 86400)
        sprintf(ut, "%02d:%02d", (t % 86400) / 3600, (t % 3600) / 60);
    if (t < 3600)
        sprintf(ut, "%02d min", (t % 3600) / 60);
}

void disp_head_top(main_t *main)
{
    char uptime[30] = {0};
    char *users = (main->info.header_top.users > 1) ? "rs" : "s";
    fill_time(uptime, main->info.header_top.uptime);

    sprintf(main->disp.line_top, HDR_TOP,
        main->info.header_top.cur_time,
        uptime,
        main->info.header_top.users,
        users,
        main->info.header_top.load_avg);
    main->disp.line_top[clamp(main->ncurses.x, 0, HDR_LINE_LEN - 1)] = 0;
    printw("%s", main->disp.line_top);
}