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

static void init_first_snapshot(main_t *main)
{
    int i = 0;

    cpu_function(main);
    main->info.system_time_old = get_system_total_time();
    fetch(main);
    for (i = 0; i < 64; i++) {
        if (main->info.processes[i].pid == 0)
            break;
        main->info.processes_cpu_old[i].pid =
            main->info.processes_cpu_new[i].pid;
        main->info.processes_cpu_old[i].utime =
            main->info.processes_cpu_new[i].utime;
        main->info.processes_cpu_old[i].stime =
            main->info.processes_cpu_new[i].stime;
    }
}

static void update_cpu_data(main_t *main, unsigned int *data_time)
{
    cpu_function(main);
    cpu_calcul(main);
    main->info.system_time_new = get_system_total_time();
    *data_time = 0;
}

static int handle_refresh(main_t *main, int *first_pass)
{
    main->info.processes_total_available = count_total_processes(main);
    if (fetch(main) == EXIT_FAIL)
        return EXIT_FAIL;
    if (!(*first_pass))
        calc_processes_cpu_mem(main);
    *first_pass = 0;
    if (display(main) == EXIT_FAIL)
        return EXIT_FAIL;
    return EXIT_SUCC;
}

int main_loop(main_t *main)
{
    unsigned int time_elapsed = main->args.delay * 1000000;
    unsigned int data_time = 0;
    unsigned int frame_count = 0;
    int inputs = 0;
    int first_pass = 1;

    init_first_snapshot(main);
    while (1) {
        inputs = handle_inputs(main);
        noecho();
        if (inputs == EXIT_FAIL || inputs == WINDOW_EXIT)
            return (inputs == WINDOW_EXIT) ? EXIT_SUCC : EXIT_FAIL;
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
        if (data_time >= 100000)
            update_cpu_data(main, &data_time);
        if (handle_refresh(main, &first_pass) == EXIT_FAIL)
            return EXIT_FAIL;
        if (main->args.frames && ++frame_count >= main->args.frames)
            return EXIT_SUCC;
    }
    return EXIT_SUCC;
}