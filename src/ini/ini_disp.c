/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to initialize the str_arr_params structures.
*/

#include "./../../include/my_top.h"

static void ini_lines(main_t *main)
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

static void ini_cols(main_t *main)
{
    main->disp.cols.pid = true;
    main->disp.cols.user = true;
    main->disp.cols.pr = true;
    main->disp.cols.ni = true;
    main->disp.cols.virt = true;
    main->disp.cols.res = true;
    main->disp.cols.shr = true;
    main->disp.cols.s = true;
    main->disp.cols.cpu = true;
    main->disp.cols.mem = true;
    main->disp.cols.time = true;
    main->disp.cols.command = true;
}

static void ini_cols_ignored(main_t *main)
{
    main->disp.cols_ignored.pid = false;
    main->disp.cols_ignored.user = false;
    main->disp.cols_ignored.pr = false;
    main->disp.cols_ignored.ni = false;
    main->disp.cols_ignored.virt = false;
    main->disp.cols_ignored.res = false;
    main->disp.cols_ignored.shr = false;
    main->disp.cols_ignored.s = false;
    main->disp.cols_ignored.cpu = false;
    main->disp.cols_ignored.mem = false;
    main->disp.cols_ignored.time = false;
    main->disp.cols_ignored.command = false;
}

void ini_disp(main_t *main)
{
    ini_lines(main);
    ini_cols(main);
    ini_cols_ignored(main);
}