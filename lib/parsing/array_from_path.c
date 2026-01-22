/*
** EPITECH PROJECT, 2025
** buff_from_path
** File description:
** A function that fills a buffer from str_to_array with a path.
*/

#include "./../../include/my_top.h"

int array_from_path(const char *path, const char *sep,
    str_arr_t *par, char buffer[par->b_wrd][par->b_len])
{
    int to_read = par->b_len * par->b_wrd + 1;
    char buff[to_read];
    FILE *file = fopen(path, "r");

    if (!file)
        return 84;
    fread(buff, (size_t)to_read, 1, file);
    fclose(file);
    str_to_array(buff, sep, par, buffer);
    return 0;
}