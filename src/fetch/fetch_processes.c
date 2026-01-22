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

    if (exponent < 2) {
        sprintf(main->info.processes[*total].virt, "%i", (int)virt);
        return;
    }
    if (exponent == 2)
        sprintf(main->info.processes[*total].virt, "%.1fg", virt / exp);
    if (exponent == 3)
        sprintf(main->info.processes[*total].virt, "%.1fg", virt / exp);
}

static void parse_stat_values(char *ptr, long long *values)
{
    int idx = 0;
    int is_num = 0;

    while (*ptr && idx < 50) {
        is_num = *ptr >= '0' && *ptr <= '9';
        is_num = is_num || *ptr == '-';
        if (!is_num) {
            ptr++;
            continue;
        }
        values[idx++] = atoll(ptr);
        while (*ptr && *ptr != ' ')
            ptr++;
    }
}

static void extract_comm_name(main_t *main, int *total, char *start, char *end)
{
    int name_len = end - start - 1;
    int is_empty = main->info.processes[*total].command[0] == '\0';

    if (name_len <= 0 || name_len >= 63)
        return;
    if (!is_empty)
        return;
    strncpy(main->info.processes[*total].command, start + 1, name_len);
    main->info.processes[*total].command[name_len] = '\0';
}

static void calc_time(main_t *main, int *total, long long *values)
{
    long long total_ticks = 0;
    long long total_centisec = 0;
    int minutes = 0;
    int seconds = 0;
    int centisec = 0;

    total_ticks = values[10] + values[11] + values[12] + values[13];
    total_centisec = (total_ticks * 100) / sysconf(_SC_CLK_TCK);
    minutes = (int)(total_centisec / 6000);
    seconds = (int)((total_centisec % 6000) / 100);
    centisec = (int)(total_centisec % 100);
    sprintf(main->info.processes[*total].time, "%d:%02d.%02d",
        minutes, seconds, centisec);
}

static void calc_virt(main_t *main, int *total, long long *values)
{
    long long vsize_kb = values[19] / 1024;
    int exponent = 0;
    float virt = 0;

    exponent = (int)(log10(vsize_kb + 1) / log10(1024));
    exponent = exponent >= 2 ? exponent : 0;
    virt = (float)vsize_kb;
    parse_virt(main, total, virt, exponent);
}

static int parse_stat(FILE *file, main_t *main, int *total)
{
    char buff[512] = {0};
    char *start = NULL;
    char *end = NULL;
    long long values[50] = {0};

    fread(buff, 512, 1, file);
    start = strchr(buff, '(');
    end = strrchr(buff, ')');
    if (!end || !start)
        return EXIT_FAIL;
    main->info.processes[*total].s = *(end + 2);
    extract_comm_name(main, total, start, end);
    parse_stat_values(end + 4, values);
    main->info.processes[*total].pr = (int)values[14];
    main->info.processes[*total].ni = (int)values[15];
    calc_time(main, total, values);
    calc_virt(main, total, values);
    return EXIT_SUCC;
}

static void read_cmdline(main_t *main, int *total, FILE *file2)
{
    size_t bytes_read = 0;
    size_t i = 0;

    bytes_read = fread(main->info.processes[*total].command, 1, 63, file2);
    main->info.processes[*total].command[bytes_read] = '\0';
    for (i = 0; i < bytes_read; i++) {
        if (main->info.processes[*total].command[i] == '\0')
            main->info.processes[*total].command[i] = ' ';
    }
}

static int open_cmdline(main_t *main, int *total, char *name)
{
    FILE *file2 = NULL;
    char buff[2048] = {0};

    sprintf(buff, "/proc/%s/cmdline", name);
    file2 = fopen(buff, "r");
    if (!file2) {
        main->info.processes[*total].command[0] = '\0';
        return EXIT_SUCC;
    }
    read_cmdline(main, total, file2);
    fclose(file2);
    return EXIT_SUCC;
}

static int parse_status(FILE *file, main_t *main, int *total)
{
    char buff[2048] = {0};
    char arr[128][16] = {0};
    int i = 0;

    fread(buff, 2048, 1, file);
    str_to_array(buff, " \t\n", &(main->str_arr[PID_STATUS]), arr);
    for (i = 0; arr[i][0]; i++) {
        if (!strcmp(arr[i], "VmRSS:"))
            main->info.processes[*total].res = atoi(arr[i + 1]);
        if (!strcmp(arr[i], "RssFile:"))
            main->info.processes[*total].shr = atoi(arr[i + 1]);
        if (!strcmp(arr[i], "Uid:"))
            user_from_pid(main, atoi(arr[i + 1]), total);
    }
    return fclose(file), EXIT_SUCC;
}

static void init_process_slot(prc_t *prc)
{
    prc->pid = 0;
    prc->pr = 0;
    prc->ni = 0;
    prc->res = 0;
    prc->shr = 0;
    prc->cpu = 0.0;
    prc->mem = 0.0;
    prc->s = '?';
    prc->user[0] = '\0';
    prc->time[0] = '\0';
    prc->virt[0] = '\0';
    prc->command[0] = '\0';
}

static int open_and_parse_status(main_t *main, int *total, char *name)
{
    FILE *file = NULL;
    char path[32] = {0};

    sprintf(path, "/proc/%s/status", name);
    file = fopen(path, "r");
    if (!file)
        return EXIT_FAIL;
    if (parse_status(file, main, total) == EXIT_FAIL)
        return EXIT_FAIL;
    return open_cmdline(main, total, name);
}

static int open_and_parse_stat(main_t *main, int *total, char *name)
{
    FILE *file2 = NULL;
    char path[32] = {0};

    sprintf(path, "/proc/%s/stat", name);
    file2 = fopen(path, "r");
    if (!file2)
        return EXIT_FAIL;
    if (parse_stat(file2, main, total) == EXIT_FAIL)
        return fclose(file2), EXIT_FAIL;
    return fclose(file2), EXIT_SUCC;
}

static int parse_single_process(main_t *main, struct dirent *dp, int *total)
{
    init_process_slot(&main->info.processes[*total]);
    main->info.processes[*total].pid = atoi(dp->d_name);
    if (open_and_parse_status(main, total, dp->d_name) == EXIT_FAIL)
        return EXIT_FAIL;
    if (open_and_parse_stat(main, total, dp->d_name) == EXIT_FAIL)
        return EXIT_FAIL;
    (*total)++;
    return EXIT_SUCC;
}

static int get_uid_from_status(char *pid_name, main_t *main)
{
    char path[32];
    char buf[512];
    char arr[64][16] = {0};
    FILE *file = NULL;
    int i = 0;

    sprintf(path, "/proc/%s/status", pid_name);
    file = fopen(path, "r");
    if (!file)
        return -1;
    fread(buf, 512, 1, file);
    fclose(file);
    str_to_array(buf, " \t\n", &(main->str_arr[PID_STATUS]), arr);
    for (i = 0; arr[i][0]; i++) {
        if (!strcmp(arr[i], "Uid:"))
            return atoi(arr[i + 1]);
    }
    return -1;
}

static int match_user_with_uid(main_t *main, int uid)
{
    int i = 0;

    for (i = 0; i < 128 && main->etc_data.uid[i]; i++) {
        if (main->etc_data.uid[i] == uid)
            return !strcmp(main->etc_data.user[i], main->args.user);
    }
    return 0;
}

static int check_user_filter(main_t *main, char *pid_name)
{
    int uid = 0;

    if (!main->args.user)
        return 1;
    uid = get_uid_from_status(pid_name, main);
    if (uid == -1)
        return 0;
    return match_user_with_uid(main, uid);
}

int count_total_processes(main_t *main)
{
    DIR *dir = opendir("/proc");
    struct dirent *dp = NULL;
    int count = 0;

    if (!dir)
        return 0;
    while (1) {
        dp = readdir(dir);
        if (!dp)
            break;
        if (atoi(dp->d_name) == 0)
            continue;
        if (!check_user_filter(main, dp->d_name))
            continue;
        count++;
    }
    closedir(dir);
    return count;
}

static int process_loop(DIR *dir, main_t *main, int *total)
{
    struct dirent *dp = NULL;
    int skip = 0;

    while (1) {
        dp = readdir(dir);
        if (!dp)
            break;
        if (!atoi(dp->d_name))
            continue;
        if (!check_user_filter(main, dp->d_name))
            continue;
        if (skip++ < main->info.processes_skip)
            continue;
        if (parse_single_process(main, dp, total) == EXIT_FAIL)
            continue;
        if (*total == 64)
            break;
    }
    return EXIT_SUCC;
}

int fetch_processes(main_t *main)
{
    DIR *dir = opendir("/proc");
    int total = 0;
    int dir_amount = count_total_processes(main);

    if (!dir)
        return EXIT_FAIL;
    main->info.processes_skip = clamp(main->info.processes_skip, 0, dir_amount - main->ncurses.y + 7);
    for (int i = 0; i < 64; i++)
        init_process_slot(&main->info.processes[i]);
    process_loop(dir, main, &total);
    closedir(dir);
    return EXIT_SUCC;
}