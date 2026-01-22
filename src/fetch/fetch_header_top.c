/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to fetch header top
*/

#include "./../../include/my_top.h"

static void modify_time(char *time)
{
    time[1] += 1;
    if (time[0] == '2' && time[1] == '4') {
        time[0] = '0';
        time[1] = '0';
    }
    if (time[1] == '9' + 1) {
        time[1] = '0';
        time[0] += 1;
    }
}

static int fetch_users(main_t *main)
{
    struct utmp buf;
    FILE *file;

    main->info.header_top.users = 0;
    file = fopen(PATH_UTMP, "rb");
    if (file == NULL)
        return EXIT_FAIL;
    while (fread(&buf, sizeof(struct utmp), 1, file) == 1) {
        if (buf.ut_type == USER_PROCESS)
            main->info.header_top.users++;
    }
    fclose(file);
    return EXIT_SUCC;
}

int fetch_header_top(main_t *main)
{
    char uptime[main->str_arr[UPTIME].b_wrd][main->str_arr[UPTIME].b_len];

    if (buff_from_path(main->info.header_top.cur_time, 11,
        18, PATH_CUR_TIME) == EXIT_FAIL)
        return EXIT_FAIL;
    modify_time(main->info.header_top.cur_time);
    if (buff_from_path(main->info.header_top.load_avg, 0,
        13, PATH_LOADAVG) == EXIT_FAIL)
        return EXIT_FAIL;
    array_from_path(PATH_UPTIME, " ", &(main->str_arr[UPTIME]), uptime);
    main->info.header_top.uptime = (int)atof(uptime[0]);
    if (fetch_users(main) == EXIT_FAIL)
        return EXIT_FAIL;
    return EXIT_SUCC;
}