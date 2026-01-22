/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to initialize structure.
*/

#include "./../../include/my_top.h"

void ini_args(main_t *main)
{
    main->args.user = 0;
    main->args.delay = 3.0f;
    main->args.frames = 0;
}

void ini_ncurses(main_t *main)
{
    main->ncurses.screen = ((void *)0);
    main->ncurses.x = 0;
    main->ncurses.y = 0;
}

void ini_struct(main_t *main)
{
    ini_str_arr_params(main);
    ini_args(main);
    ini_ncurses(main);
    ini_info(main);
    ini_disp(main);
}
