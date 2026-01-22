/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to initialize the str_arr_params structures.
*/

#include "./../../include/my_top.h"

static void ini_params_etc(main_t *main)
{
    main->str_arr[ETC_PASSWD].b_len = 32;
    main->str_arr[ETC_PASSWD].b_wrd = 512;
    main->str_arr[ETC_PASSWD].skip = 0;
    main->str_arr[ETC_PASSWD].exclude = "";
}

static void ini_params_header(main_t *main)
{   
    main->str_arr[UPTIME].b_len = 10;
    main->str_arr[UPTIME].b_wrd = 2;
    main->str_arr[UPTIME].skip = 0;
    main->str_arr[UPTIME].exclude = "";
    main->str_arr[UTMP].b_len = 100;
    main->str_arr[UTMP].b_wrd = 10;
    main->str_arr[UTMP].skip = 1;
    main->str_arr[UTMP].exclude = "";
    main->str_arr[MEMINFO].b_len = 32;
    main->str_arr[MEMINFO].b_wrd = 256;
    main->str_arr[MEMINFO].skip = 0;
    main->str_arr[MEMINFO].exclude = "";
    main->str_arr[STAT].b_len = 15;
    main->str_arr[STAT].b_wrd = 10;
    main->str_arr[STAT].skip = 1;
    main->str_arr[STAT].exclude = "";
}

static void ini_params_pid(main_t *main)
{
    main->str_arr[PID_STAT].b_len = 16;
    main->str_arr[PID_STAT].b_wrd = 32;
    main->str_arr[PID_STAT].skip = 0;
    main->str_arr[PID_STAT].exclude = "";
    main->str_arr[PID_STATUS].b_len = 16;
    main->str_arr[PID_STATUS].b_wrd = 128;
    main->str_arr[PID_STATUS].skip = 0;
    main->str_arr[PID_STATUS].exclude = "";
}

void ini_str_arr_params(main_t *main)
{
    ini_params_header(main);
    ini_params_etc(main);
    ini_params_pid(main);
}