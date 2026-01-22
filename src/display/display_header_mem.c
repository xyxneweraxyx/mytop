/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../../include/my_top.h"

void disp_head_mem(main_t *main)
{
    sprintf(main->disp.line_mem, HDR_MEM,
        main->info.header_mem.total,
        main->info.header_mem.free,
        main->info.header_mem.used,
        main->info.header_mem.cache
    );
    main->disp.line_mem[clamp(main->ncurses.x, 0, HDR_LINE_LEN - 1)] = 0;
    printw("%s", main->disp.line_mem);
}