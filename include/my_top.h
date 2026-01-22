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
    #include <string.h>
    #include <utmp.h>
    #include <sys/types.h>
    #include <dirent.h>

    // RETURN CODES
    #define EXIT_SUCC 0
    #define EXIT_FAIL 84
    #define WINDOW_RESIZE 100
    #define WINDOW_EXIT 101
    #define INSTANT_REFRESH 102

    // MISC
    #define MIN_DELAY 1000
    #define ARRAY_STR_LEN 64
    #define HDR_LINE_LEN 128

    // GETCH CODES
    #define GETCH_EXIT 113
    #define GETCH_RESIZE -102
    #define GETCH_DOWN 66
    #define GETCH_UP 65

    // FILEPATHS
    #define PATH_CUR_TIME "/proc/driver/rtc"
    #define PATH_UPTIME "/proc/uptime"
    #define PATH_LOADAVG "/proc/loadavg"
    #define PATH_UTMP "/run/utmp"
    #define PATH_TASKS "/proc/stat"

    // FORMATS
    #define HDR_TOP "top - %s up %s, %d use%s, load average: %s\n"
    #define HDR_TASK "Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie\n"
    #define HDR_CPU "%%Cpu(s): %.1f us, %.1f sy, %.1f ni, %.1f id, %.1f wa, %.1f hi, %.1f si, %.1f st\n"
    #define HDR_MEM "MiB Mem : %8.1f total, %8.1f free, %8.1f used, %8.1f buff/cache\n"
    #define HDR_SWAP "MiB Swap: %8.1f total, %8.1f free, %8.1f used, %8.1f avail Mem"
    #define PRC_WHITE "    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND"
    #define PRC_LINE "%7d %-7.7s %4d %3d %7s %6d %6d %c %5.1f %5.1f %9s %-s" // what the fuck

typedef struct str_arr {
    int skip; // Amount of words to potentially skip before writing to buffer
    int b_wrd; // Amount of words in buffer.
    int b_len; // Length of a single word in buffer.
    const char *exclude; // Characters to ignore.
} str_arr_t;

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

typedef struct prc {
    int pid;
    char user[32];
    int pr;
    int ni;
    char virt[8];
    int res;
    int shr;
    char s;
    float cpu;
    float mem;
    char time[16];
    char command[64];
} prc_t;

typedef struct disp {
    char line_top[128];
    char line_tasks[128];
    char line_cpu[128];
    char line_mem[128];
    char line_swap[128];
    cols_shown_t cols_ignored;
    cols_shown_t cols;
} disp_t;

typedef struct header_top {
    char cur_time[10];
    unsigned int uptime;
    int users;
    char load_avg[15];
} header_top_t;

typedef struct header_tasks {
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
} header_tasks_t;

typedef struct header_cpu {
    float us;
    float sy;
    float ni;
    float id;
    float wa;
    float hi;
    float si;
    float st;
} header_cpu_t;

typedef struct header_mem {
    float total;
    float free;
    float used;
    float cache;
} header_mem_t;

typedef struct header_swap {
    float total;
    float free;
    float used;
    float avail;
} header_swap_t;

typedef struct info {
    header_top_t header_top;
    header_tasks_t header_tasks;
    float header_cpu_old[10];
    float header_cpu_new[10];
    header_cpu_t header_cpu;
    header_mem_t header_mem;
    header_swap_t header_swap;
    prc_t processes[64];
    int processes_skip;
} info_t;

typedef enum str_param {
    UPTIME,
    UTMP,
    MEMINFO,
    STAT,
    ETC_PASSWD,
    PID_STAT,
    PID_STATUS
} str_param_t;

typedef struct etc_data {
    int uid[128];
    char user[128][32];
} etc_data_t;

typedef struct main {
    args_t args;
    ncurses_t ncurses;
    disp_t disp;
    info_t info;
    str_arr_t str_arr[7];
    etc_data_t etc_data;
} main_t;

/// LIB FILES

// LIB MATH FILES
int clamp(int x, int min, int max);
float clampf(float x, float min, float max);

// LIB STR FILES
int str_len(const char *str);
int char_in_str(const char c, const char *str);
void str_to_array(const char *str, const char *sep, str_arr_t *par,
    char buf[par->b_wrd][par->b_len]);

// LIB PARSING FILES
int buff_from_path(char *buf, int st, int end, char *path);
int array_from_path(const char *path, const char *sep,
    str_arr_t *par, char buffer[par->b_wrd][par->b_len]);

/// SRC FILES
void ini_struct(main_t *main);
void ini_str_arr_params(main_t *main);
void ini_info(main_t *main);
void ini_disp(main_t *main);

int parse_args(int argc, char **argv, main_t *main);
int etc_parser(main_t *main);
int user_from_pid(main_t *main, int pid, int *total);
int main_loop(main_t *main);

int fetch(main_t *main);
int fetch_header_tasks(main_t *main);
int fetch_header_top(main_t *main);
int fetch_header_cpu(main_t *main);
int cpu_function(main_t *main);
void cpu_calcul(main_t *main);
int fetch_header_mem_swap(main_t *main);
int fetch_processes(main_t *main);

int display(main_t *main);
void disp_head_top(main_t *main);
void disp_head_tasks(main_t *main);
void disp_head_cpu(main_t *main);
void disp_head_mem(main_t *main);
void disp_head_swap(main_t *main);
void display_processes(main_t *main);

#endif
