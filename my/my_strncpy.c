/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-bsminishell2-louis.chedru
** File description:
** my_strncpy
*/

#include "my.h"
#include <stdlib.h>

char *my_strndup(char *src, int n)
{
    if (n >= my_strlen(src)) return NULL;
    char *res = malloc(sizeof(char) * (my_strlen(src) - n + 1));
    for (int i = 0; src[n] ; i++, n++) {
        res[i] = src[n];
    }
    return res;
}
