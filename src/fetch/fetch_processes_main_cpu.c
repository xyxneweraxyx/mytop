/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Calculate %CPU and %MEM for processes
*/

#include "./../../include/my_top.h"

long long get_system_total_time(void)
{
    FILE *file = fopen("/proc/stat", "r");
    char buf[256];
    long long total = 0;
    int i = 0;

    if (!file)
        return 0;
    fgets(buf, sizeof(buf), file);
    fclose(file);
    for (i = 5; buf[i]; i++) {
        if (buf[i] >= '0' && buf[i] <= '9')
            total += atoll(&buf[i]);
        while (buf[i] && buf[i] != ' ')
            i++;
    }
    return total;
}

static int find_old_by_pid(main_t *main, int pid)
{
    int i = 0;

    for (i = 0; i < 64; i++) {
        if (main->info.processes_cpu_old[i].pid == pid)
            return i;
    }
    return -1;
}

static float calc_single_cpu(main_t *main, int idx)
{
    long long new_time = 0;
    long long old_time = 0;
    long long delta_process = 0;
    long long delta_system = 0;
    int old_idx = 0;

    new_time = main->info.processes_cpu_new[idx].utime +
        main->info.processes_cpu_new[idx].stime;
    old_idx = find_old_by_pid(main,
        main->info.processes_cpu_new[idx].pid);
    if (old_idx == -1)
        return 0.0;
    old_time = main->info.processes_cpu_old[old_idx].utime +
        main->info.processes_cpu_old[old_idx].stime;
    delta_process = new_time - old_time;
    delta_system = main->info.system_time_new - main->info.system_time_old;
    if (delta_system == 0)
        return 0.0;
    return ((float)delta_process / (float)delta_system) * 100.0;
}

static float calc_single_mem(main_t *main, int idx)
{
    float res_kb = (float)main->info.processes[idx].res;
    float total_kb = main->info.header_mem.total * 1024.0;

    if (total_kb == 0)
        return 0.0;
    return (res_kb / total_kb) * 100.0;
}

static void copy_new_to_old(main_t *main)
{
    int i = 0;

    for (i = 0; i < 64; i++) {
        main->info.processes_cpu_old[i].pid =
            main->info.processes_cpu_new[i].pid;
        main->info.processes_cpu_old[i].utime =
            main->info.processes_cpu_new[i].utime;
        main->info.processes_cpu_old[i].stime =
            main->info.processes_cpu_new[i].stime;
    }
}

void calc_processes_cpu_mem(main_t *main)
{
    int i = 0;

    for (i = 0; i < 64; i++) {
        if (main->info.processes[i].pid == 0)
            break;
        main->info.processes[i].cpu = calc_single_cpu(main, i);
        main->info.processes[i].mem = calc_single_mem(main, i);
    }
    copy_new_to_old(main);
}