/*
** EPITECH PROJECT, 2025
** my_top
** File description:
** File to parse the argv.
*/

#include "./../include/my_top.h"

static int write_user(char **argv, int i, main_t *main)
{
    if (str_len(argv[i]) != 2)
        return EXIT_FAIL;
    if (!argv[i + 1])
        return EXIT_FAIL;
    if (!str_len(argv[i + 1]))
        return EXIT_FAIL;
    main->args.user = argv[i + 1];
    return EXIT_SUCC;
}

static int write_delay(char **argv, int i, main_t *main)
{
    if (str_len(argv[i]) != 2)
        return EXIT_FAIL;
    if (!argv[i + 1])
        return EXIT_FAIL;
    if (!str_len(argv[i + 1]))
        return EXIT_FAIL;
    main->args.delay = atof(argv[i + 1]);
    return EXIT_SUCC;
}

static int write_frames(char **argv, int i, main_t *main)
{
    if (str_len(argv[i]) != 2)
        return EXIT_FAIL;
    if (!argv[i + 1])
        return EXIT_FAIL;
    if (!str_len(argv[i + 1]))
        return EXIT_FAIL;
    main->args.frames = (unsigned int)atoi(argv[i + 1]);
    return EXIT_SUCC;
}

int parse_args(int argc, char **argv, main_t *main)
{
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && char_in_str(argv[i][1], "Udn") == -1)
            return EXIT_FAIL;
        if (argv[i][0] == '-' && argv[i][1] == 'U' &&
            write_user(argv, i, main) == EXIT_FAIL)
            return EXIT_FAIL;
        if (argv[i][0] == '-' && argv[i][1] == 'd' &&
            write_delay(argv, i, main) == EXIT_FAIL)
            return EXIT_FAIL;
        if (argv[i][0] == '-' && argv[i][1] == 'n' &&
            write_frames(argv, i, main) == EXIT_FAIL)
            return EXIT_FAIL;
    }
    return EXIT_SUCC;
}