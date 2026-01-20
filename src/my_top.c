/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Main file.
*/

#include "./../include/my_top.h"

static void end_program(main_t *main)
{
    delwin(main->ncurses.screen);
    endwin();
    refresh();
}

void handler(int status)
{
    endwin();
    exit(status);
}

static int ini_ncurses(main_t *main)
{
    WINDOW *screen;

    signal(SIGSEGV, handler);
    screen = initscr();
    if (!screen)
        return EXIT_FAIL;
    main->ncurses.screen = screen;
    nodelay(screen, true);
    cbreak();
    curs_set(0);
    return EXIT_SUCC;
}

int main(int argc, char **argv)
{
    main_t main = {};

    ini_struct(&main);
    if (parse_args(argc, argv, &main) == EXIT_FAIL)
        return EXIT_FAIL;
    if (ini_ncurses(&main) == EXIT_FAIL)
        return EXIT_FAIL;
    getmaxyx(main.ncurses.screen, main.ncurses.y, main.ncurses.x);
    if (main_loop(&main) == EXIT_FAIL)
        return EXIT_FAIL;
    end_program(&main);
    return EXIT_SUCC;
}