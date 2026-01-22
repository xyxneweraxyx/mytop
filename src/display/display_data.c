/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../../include/my_top.h"

static void print_white_line(main_t *main)
{
    char buff[128] = {0};

    sprintf(buff, "%s", PRC_WHITE);
    if (!main->disp.cols.command)
        buff[70] = 0;
    if (!main->disp.cols.time)
        buff[62] = 0;
    if (!main->disp.cols.mem)
        buff[55] = 0;
    if (!main->disp.cols.cpu)
        buff[49] = 0;
    if (!main->disp.cols.s)
        buff[47] = 0;
    if (!main->disp.cols.shr)
        buff[40] = 0;
    if (!main->disp.cols.res)
        buff[33] = 0;
    mvprintw(6, 0, "%s", buff);
}

static void update_cols(main_t *main)
{
    main->disp.cols.pid = (main->ncurses.x > 7) ? true : false;
    main->disp.cols.user = (main->ncurses.x > 13) ? true : false;
    main->disp.cols.pr = (main->ncurses.x > 20) ? true : false;
    main->disp.cols.ni = (main->ncurses.x > 25) ? true : false;
    main->disp.cols.virt = (main->ncurses.x > 32) ? true : false;
    main->disp.cols.res = (main->ncurses.x > 39) ? true : false;
    main->disp.cols.shr = (main->ncurses.x > 46) ? true : false;
    main->disp.cols.s = (main->ncurses.x > 48) ? true : false;
    main->disp.cols.cpu = (main->ncurses.x > 54) ? true : false;
    main->disp.cols.mem = (main->ncurses.x > 61) ? true : false;
    main->disp.cols.time = (main->ncurses.x > 71) ? true : false;
    main->disp.cols.command = (main->ncurses.x > 79) ? true : false;
}

static void display_header(main_t *main)
{
    disp_head_top(main);
    disp_head_tasks(main);
    disp_head_cpu(main);
    disp_head_mem(main);
    disp_head_swap(main);
}

int display(main_t *main)
{
    int early = 0;

    if (early) {
        refresh();
        return EXIT_SUCC;
    }
    wclear(main->ncurses.screen);
    update_cols(main);
    display_header(main);
    print_white_line(main);
    display_processes(main);
    refresh();
    return EXIT_SUCC;
}