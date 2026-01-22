/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../../include/my_top.h"

void disp_head_tasks(main_t *main)
{
    sprintf(main->disp.line_tasks, HDR_TASK,
        main->info.header_tasks.total,
        main->info.header_tasks.running,
        main->info.header_tasks.sleeping,
        main->info.header_tasks.stopped,
        main->info.header_tasks.zombie);
    main->disp.line_tasks[clamp(main->ncurses.x, 0, HDR_LINE_LEN - 1)] = 0;
    printw("%s", main->disp.line_tasks);
}