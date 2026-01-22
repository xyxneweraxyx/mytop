/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to parse etc/passwd
*/

#include "./../include/my_top.h"

void stock_user(main_t *main, int uid, char *name, int total)
{
    main->etc_data.uid[total] = uid;
    for (int i = 0; name[i]; i++)
        main->etc_data.user[total][i] = name[i];
}

int user_from_pid(main_t *main, int pid, int *total)
{
    int i = 0;
    int j = 0;
    
    if (!pid) {
        main->info.processes[*total].user[0] = 'r';
        main->info.processes[*total].user[1] = 'o';
        main->info.processes[*total].user[2] = 'o';
        main->info.processes[*total].user[3] = 't';
        main->info.processes[*total].user[4] = 0;
        return EXIT_SUCC;
    }
    for (; i < 128 && pid != main->etc_data.uid[i]; i++);
    if (i == 128)
        return EXIT_FAIL;
    for (; main->etc_data.user[i][j]; j++)
        main->info.processes[*total].user[j] = main->etc_data.user[i][j];
    main->info.processes[*total].user[j] = 0;
    return EXIT_SUCC;
}

int etc_parser(main_t *main)
{
    FILE *file = fopen("/etc/passwd", "r");
    char buff[8192] = {0};
    char arr[512][32] = {{0}};
    int total = 0;
    
    if (!file)
        return EXIT_FAIL;
    fread(buff, 8192, 1, file);
    str_to_array(buff, ":\n", &(main->str_arr[ETC_PASSWD]), arr);
    for (int i = 3; arr[i][0]; i++) {
        if (atoi(arr[i]) && !atoi(arr[i - 1])) {
            stock_user(main, atoi(arr[i]), arr[i - 2], total);
            total++;
        }
        if (total == 128)
            break;
    }
    fclose(file);
    return EXIT_SUCC;
}