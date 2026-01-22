/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../../include/my_top.h"

static void fix_cpu(main_t *main)
{
    if (main->info.header_cpu.us <= 0)
        main->info.header_cpu.us = 0;
    if (main->info.header_cpu.sy <= 0)
        main->info.header_cpu.sy = 0;
    if (main->info.header_cpu.ni <= 0)
        main->info.header_cpu.ni = 0;
    if (main->info.header_cpu.id <= 0)
        main->info.header_cpu.id = 0;
    if (main->info.header_cpu.wa <= 0)
        main->info.header_cpu.wa = 0;
    if (main->info.header_cpu.hi <= 0)
        main->info.header_cpu.hi = 0;
    if (main->info.header_cpu.si <= 0)
        main->info.header_cpu.si = 0;
    if (main->info.header_cpu.st <= 0)
        main->info.header_cpu.st = 0;
}

void disp_head_cpu(main_t *main)
{
    fix_cpu(main);
    sprintf(main->disp.line_cpu, HDR_CPU,
        main->info.header_cpu.us,
        main->info.header_cpu.sy,
        main->info.header_cpu.ni,
        main->info.header_cpu.id,
        main->info.header_cpu.wa,
        main->info.header_cpu.hi,
        main->info.header_cpu.si,
        main->info.header_cpu.st
    );
    main->disp.line_cpu[clamp(main->ncurses.x, 0, HDR_LINE_LEN - 1)] = 0;
    printw("%s", main->disp.line_cpu);
}