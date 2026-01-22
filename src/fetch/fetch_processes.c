/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to fetch header top
*/

#include "./../../include/my_top.h"

static void parse_virt(main_t *main, int *total, float virt, int exponent)
{
    int exp = pow(1024, 2);

    if (exponent >= 2) {
        if (exponent == 2)
            sprintf(main->info.processes[*total].virt, "%.1fg", virt / exp);
        if (exponent == 3)
            sprintf(main->info.processes[*total].virt, "%.1fg", virt / exp);
        return;
    }
    sprintf(main->info.processes[*total].virt, "%i", (int)virt);
}

static int parse_stat(FILE *file, main_t *main, int *total)
{
    char buff[512] = {0};
    char arr[32][16] = {{0}};
    float time = 0;
    int exponent = 0;
    float virt = 0;

    fread(buff, 512, 1, file);
    str_to_array(buff, " ", &(main->str_arr[PID_STAT]), arr);
    main->info.processes[*total].pr = atoi(arr[17]);
    main->info.processes[*total].ni = atoi(arr[18]);
    time = (float)(atoi(arr[13]) + atoi(arr[14]) + atoi(arr[15]) +
    atoi(arr[16])) / (float)sysconf(_SC_CLK_TCK);
    sprintf(main->info.processes[*total].time, "%d:%02d.%02d",
        (int)(time / 60), ((int)time % 60), (int)((time - (int)time)*100));
    exponent = (int)(log10((atoll(arr[22]) / 1024) + 1) / log10(1024));
    exponent = (exponent >= 2) ? exponent : 0;
    virt = (float)(atoll(arr[22]) / 1024);
    parse_virt(main, total, virt, exponent);
    main->info.processes[*total].s = arr[2][0];
    return EXIT_SUCC;
}

static int parse_status_cmdline(FILE *file, main_t *main,
    int *total, char *name)
{
    FILE *file2;
    char buff[2048] = {0};
    char arr[128][16] = {0};

    fread(buff, 2048, 1, file);
    str_to_array(buff, " \t\n", &(main->str_arr[PID_STATUS]), arr);
    for (int i = 0; arr[i][0]; i++) {
        if (!strcmp(arr[i], "VmRSS:")) {
            main->info.processes[*total].res = atoi(arr[i + 1]);
        }
        if (!strcmp(arr[i], "RssFile:"))
            main->info.processes[*total].shr = atoi(arr[i + 1]);
        if (!strcmp(arr[i], "Uid:"))
            user_from_pid(main, atoi(arr[i + 1]), total);
    }
    fclose(file);
    sprintf(buff, "/proc/%s/cmdline", name);
    file2 = fopen(buff, "r");
    if (!file2)
        return EXIT_FAIL;
    fread(buff, 64, 1, file2);
    for (int i = 0; buff[i]; i++)
        main->info.processes[*total].command[i] = buff[i];
    return EXIT_SUCC;
}

static int parse_single_process(main_t *main, struct dirent *dp, int *total)
{
    FILE *file;
    FILE *file2;
    char path[32] = {0};

    main->info.processes[*total].pid = atoi(dp->d_name);
    sprintf(path, "/proc/%s/status", dp->d_name);
    file = fopen(path, "r");
    if (!file)
        return EXIT_FAIL;
    if (parse_status_cmdline(file, main, total, dp->d_name) == EXIT_FAIL) {
        fclose(file);
        return EXIT_FAIL;
    }
    fclose(file);
    sprintf(path, "/proc/%s/stat", dp->d_name);
    file2 = fopen(path, "r");
    if (!file2)
        return EXIT_FAIL;
    if (parse_stat(file, main, total) == EXIT_FAIL) {
        fclose(file2);
        return EXIT_FAIL;
    }
    fclose(file2);
    (*total)++;
    return EXIT_SUCC;
}

int fetch_processes(main_t *main)
{
    DIR *dir = opendir("/proc");
    struct dirent *dp;
    int skip = 0;
    int total = 0;
    bool failed = false;

    if (!dir)
        return EXIT_FAIL;
    while (1) {
        dp = readdir(dir);
        if (!dp)
            break;
        if (!atoi(dp->d_name))
            continue;
        if (skip < main->info.processes_skip) {
            skip++;
            continue;
        }
        if (parse_single_process(main, dp, &total) == EXIT_FAIL) {
            failed = true;
            break;
        }
        if (total == 64)
            break;
    }
    closedir(dir);
    return failed ? EXIT_FAIL : EXIT_SUCC;
}