/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to initialize structure.
*/

#include "./../include/my_top.h"

void ini_args(main_t *main)
{
    main->args.user = 0;
    main->args.delay = 3.0f;
    main->args.frames = 0;
}

void ini_ncurses(main_t *main)
{
    main->ncurses.screen = ((void *)0);
    main->ncurses.x = 0;
    main->ncurses.y = 0;
}

void ini_info(main_t *main)
{
    for (int i = 0; i < 10; i++)
        main->info.header_top.cur_time[i] = 0;
    for (int i = 0; i < 15; i++)
        main->info.header_top.load_avg[i] = 0;
}

void ini_disp(main_t *main)
{
    for (int i = 0; i < 128; i++)
        main->disp.line_top[i] = 0;
    for (int i = 0; i < 128; i++)
        main->disp.line_cpu[i] = 0;
    for (int i = 0; i < 128; i++)
        main->disp.line_mem[i] = 0;
    for (int i = 0; i < 128; i++)
        main->disp.line_swap[i] = 0;
    for (int i = 0; i < 128; i++)
        main->disp.line_tasks[i] = 0;
}

void ini_struct(main_t *main)
{
    ini_args(main);
    ini_ncurses(main);
    ini_info(main);
    ini_disp(main);
}
