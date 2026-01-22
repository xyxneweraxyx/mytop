/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../../include/my_top.h"

static void format_buffer(main_t *main, char buff[128])
{
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
}

void display_processes(main_t *main)
{
    char buff[128] = {0};
    prc_t *prc = NULL;

    for (int i = 0; i < 64; i++)
    {
        prc = &(main->info.processes[i]);
        sprintf(buff, PRC_LINE, prc->pid, prc->user, prc->pr, prc->ni,
            prc->virt, prc->res, prc->shr, prc->s, prc->cpu, prc->mem,
            prc->time, prc->command);
        format_buffer(main, buff);
        mvprintw(7 + i, 0, "%s", buff);
    }
}