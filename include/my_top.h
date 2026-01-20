/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** Header file.
*/

#ifndef MY_TOP
    #define MY_TOP

    #include <ncurses.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <unistd.h>
    #include <signal.h>
    #include <math.h>

    // RETURN CODES
    #define EXIT_SUCC 0
    #define EXIT_FAIL 84
    #define WINDOW_RESIZE 100
    #define WINDOW_EXIT 101

    // MISC
    #define MIN_DELAY 1000
    #define ARRAY_STR_LEN 64
    #define HDR_LINE_LEN 128

    // GETCH CODES
    #define GETCH_EXIT 113
    #define GETCH_RESIZE -102

    // FILEPATHS
    #define PATH_CUR_TIME "/proc/driver/rtc"
    #define PATH_UPTIME "/proc/uptime"
    #define PATH_LOADAVG "/proc/loadavg"

    // FORMATS
    #define HDR_TOP "top - %s up %s, %d user, load average: %s\n"
    #define HDR_TASK "Tasks: %s total, %s running, %s sleeping, %s stopped, %s zombie\n"
    #define HDR_CPU "%%Cpu(s): %s us, %s sy, %s ni, %s id, %s wa, %s hi, %s si, %s st\n"
    #define HDR_MEM "MiB Mem : %s total, %s free, %s used, %s buff/cache\n"
    #define HDR_SWAP "MiB Swap: %s total, %s free, %s used, %s avail Mem\n"
    #define PRC_WHITE "    PID USER      PR  NI    VIRT    RES    SHR S  %%CPU  %%MEM     TIME+ COMMAND\n"
    #define PRC_LINE "%s%s%s%s%s%s%s%s%s%s%s%s\n" // what the fuck

typedef struct args {
    char *user;
    double delay;
    unsigned int frames;
} args_t;

typedef struct ncurses {
    WINDOW *screen;
    int x;
    int y;
} ncurses_t;

typedef struct cols_shown {
    bool pid;
    bool user;
    bool pr;
    bool ni;
    bool virt;
    bool res;
    bool shr;
    bool s;
    bool cpu;
    bool mem;
    bool time;
    bool command;
} cols_shown_t;

typedef struct disp {
    char line_top[128];
    char line_tasks[128];
    char line_cpu[128];
    char line_mem[128];
    char line_swap[128];
    cols_shown_t cols;
} disp_t;

typedef struct header_top {
    char cur_time[10];
    unsigned int uptime;

    uint8_t users;
    char load_avg[15];
} header_top_t;

typedef struct info {
    header_top_t header_top;
} info_t;

typedef struct main {
    args_t args;
    ncurses_t ncurses;
    disp_t disp;
    info_t info;
} main_t;

/// LIB FILES

// LIB MATH FILES
int clamp(int x, int min, int max);
double clampf(double x, double min, double max);

// LIB STR FILES
int str_len(const char *str);
int char_in_str(const char c, const char *str);
int str_to_array(const char *str, const char *sep, int max, char buf[max][64]);

// LIB PARSING FILES
int buff_from_path(char *buf, int st, int end, char *path);

/// SRC FILES

void ini_struct(main_t *main);
int parse_args(int argc, char **argv, main_t *main);
int main_loop(main_t *main);
int fetch(main_t *main);
int display(main_t *main);

#endif
