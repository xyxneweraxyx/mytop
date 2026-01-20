/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../include/my_top.h"

static void display_header(main_t *main)
{
    sprintf(main->disp.line_top, HDR_TOP,
        main->info.header_top.cur_time, main->info.header_top.load_avg);
    main->disp.line_top[clamp(main->ncurses.x, 0, HDR_LINE_LEN - 1)] = 0;
    printw("%s\n", main->disp.line_top);
}

int display(main_t *main)
{
    wclear(main->ncurses.screen);
    display_header(main);
    refresh();
    return EXIT_SUCC;
}