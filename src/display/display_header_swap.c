/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../../include/my_top.h"

void disp_head_swap(main_t *main)
{
    sprintf(main->disp.line_swap, HDR_SWAP,
        main->info.header_swap.total,
        main->info.header_swap.free,
        main->info.header_swap.used,
        main->info.header_swap.avail
    );
    main->disp.line_swap[clamp(main->ncurses.x, 0, HDR_LINE_LEN - 1)] = 0;
    printw("%s", main->disp.line_swap);
}