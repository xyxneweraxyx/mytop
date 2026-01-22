/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../include/my_top.h"

int handle_inputs(main_t *main)
{
    char character = getch();

    if (character == GETCH_EXIT)
        return WINDOW_EXIT;
    if (character == GETCH_RESIZE) {
        getmaxyx(main->ncurses.screen, main->ncurses.y, main->ncurses.x);
        return WINDOW_RESIZE;
    }
    if (character == GETCH_DOWN) {
        main->info.processes_skip++;
        return INSTANT_REFRESH;
    }
    if (character == GETCH_UP && main->info.processes_skip > 0) {
        main->info.processes_skip--;
        return INSTANT_REFRESH;
    }
    return EXIT_SUCC;
}

int main_loop(main_t *main)
{
    unsigned int time_elapsed = main->args.delay * 1000000;
    unsigned int data_time = 0;
    unsigned int frame_count = 0;
    int inputs = 0;
    int fetched = 0;

    while (1) {
        inputs = handle_inputs(main);
        noecho();
        if (!fetched) {
            cpu_function(main);
            main->info.system_time_old = get_system_total_time();
            fetched = 1;
        }
        if (inputs == EXIT_FAIL)
            return EXIT_FAIL;
        if (inputs == WINDOW_EXIT)
            return EXIT_SUCC;
        if (inputs == INSTANT_REFRESH)
            time_elapsed = main->args.delay * 1000000;
        if (time_elapsed < main->args.delay * 1000000 && inputs == EXIT_SUCC) {
            usleep(MIN_DELAY);
            time_elapsed += MIN_DELAY;
            data_time += MIN_DELAY;
            continue;
        }
        time_elapsed = 0;
        data_time += MIN_DELAY;
        if (data_time >= 100000) {
            fetched = 0;
            cpu_function(main);
            cpu_calcul(main);
            main->info.system_time_new = get_system_total_time();
            calc_processes_cpu_mem(main);
            main->info.system_time_old = main->info.system_time_new;
            data_time = 0;
        }
        main->info.processes_total_available = count_total_processes(main);
        if (fetch(main) == EXIT_FAIL || display(main) == EXIT_FAIL)
            return EXIT_FAIL;
        if (main->args.frames && ++frame_count >= main->args.frames)
            return EXIT_SUCC;
    }
    return EXIT_SUCC;
}