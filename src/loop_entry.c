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
    int inputs = 0;
    int fetched = 0;

    while (1) {
        inputs = handle_inputs(main);
        noecho();
        if (!fetched) {
            cpu_function(main);
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
            continue;
        }
        time_elapsed = 0;
        fetched = 0;
        cpu_function(main);
        cpu_calcul(main);
        if (fetch(main) == EXIT_FAIL || display(main) == EXIT_FAIL)
            return EXIT_FAIL;
    }
    return EXIT_SUCC;
}