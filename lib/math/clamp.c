/*
** EPITECH PROJECT, 2025
** clamp
** File description:
** Functions that clamp numbers.
*/

int clamp(int x, int min, int max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}

float clampf(float x, float min, float max)
{
    if (x < min)
        return min;
    if (x > max)
        return max;
    return x;
}