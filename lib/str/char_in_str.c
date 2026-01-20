/*
** EPITECH PROJECT, 2025
** char_in_str
** File description:
** A function that attempts to find a char in a given string.
*/

#include <stdio.h>

int char_in_str(const char c, const char *str)
{
    int i = 0;

    for (i = 0; str[i] != c && str[i]; i++);
    return (str[i] == 0) ? -1 : i;
}
