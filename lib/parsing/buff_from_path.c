/*
** EPITECH PROJECT, 2025
** buff_from_path
** File description:
** A function that fills a buffer with a filepath.
*/

#include <stdio.h>
#include <unistd.h>

int buff_from_path(char *buf, int st, int end, char *path)
{
    FILE *file = fopen(path, "r");
    char useless[st + 1];

    if (!file)
        return 84;
    for (int i = 0; i < st + 1; i++)
        useless[i] = 0;
    fread(useless, 1, st, file);
    fread(buf, 1, end - st + 1, file);
    fclose(file);
    return 0;
}
