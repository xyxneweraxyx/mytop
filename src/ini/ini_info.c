/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to initialize the str_arr_params structures.
*/

#include "./../../include/my_top.h"

static void ini_header_one(main_t *main)
{
    for (int i = 0; i < 10; i++)
        main->info.header_top.cur_time[i] = 0;
    for (int i = 0; i < 15; i++)
        main->info.header_top.load_avg[i] = 0;
    main->info.header_top.uptime = 0;
    main->info.header_top.users = 0;
    main->info.header_tasks.total = 0;
    main->info.header_tasks.running = 0;
    main->info.header_tasks.sleeping = 0;
    main->info.header_tasks.stopped = 0;
    main->info.header_tasks.zombie = 0;
    main->info.header_cpu.us = 0;
    main->info.header_cpu.sy = 0;
    main->info.header_cpu.ni = 0;
    main->info.header_cpu.id = 0;
    main->info.header_cpu.wa = 0;
    main->info.header_cpu.hi = 0;
    main->info.header_cpu.si = 0;
    main->info.header_cpu.st = 0;
}

static void ini_header_two(main_t *main)
{
    main->info.header_mem.total = 0;
    main->info.header_mem.free = 0;
    main->info.header_mem.used = 0;
    main->info.header_mem.cache = 0;
    main->info.header_swap.total = 0;
    main->info.header_swap.free = 0;
    main->info.header_swap.used = 0;
    main->info.header_swap.avail = 0;
}

void ini_processes(main_t *main)
{
    for (int i = 0; i < 64; i++) {
        for (int j = 0; j < 64; j++)
            main->info.processes[i].command[j] = 0;
        for (int j = 0; j < 32; j++)
            main->info.processes[i].user[j] = 0;
        for (int j = 0; j < 16; j++)
            main->info.processes[i].time[j] = 0;
        for (int j = 0; j < 8; j++)
            main->info.processes[i].virt[j] = 0;
        main->info.processes[i].pid = 0;
        main->info.processes[i].pr = 0;
        main->info.processes[i].ni = 0;
        main->info.processes[i].res = 0;
        main->info.processes[i].shr = 0;
        main->info.processes[i].cpu = 0;
        main->info.processes[i].mem = 0;
    }
    main->info.processes_skip = 0;
}

void ini_info(main_t *main)
{
    ini_header_one(main);
    ini_header_two(main);
    ini_processes(main);
}