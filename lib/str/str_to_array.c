/*
** EPITECH PROJECT, 2025
** str_to_array
** File description:
** Convert a string to an array based on a number of seps and a max amount.
*/

static int c_s(const char c, const char *str)
{
    int i = 0;

    for (i = 0; str[i] != c && str[i]; i++);
    return (str[i] == 0) ? -1 : i;
}

int str_to_array(const char *str, const char *sep, int max, char buf[max][64])
{
    int w = 0;
    int cur = 0;

    for (int i = 0; c_s(str[i], sep) != -1 && str[i]; str++);
    buf[0][0] = (c_s(str[0], sep) != -1) ? 0 : str[0];
    for (int i = 0; str[i] && w < max; i++) {
        if (c_s(str[i], sep) == -1) {
            buf[w][cur] = str[i];
            cur++;
        }
        if ((c_s(str[i], sep) != -1) && (c_s(str[i + 1], sep) == -1)) {
            cur = 0;
            w += 1;
        }
    }
    return 0;
}