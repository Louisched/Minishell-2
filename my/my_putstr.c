/*
** EPITECH PROJECT, 2022
** my_put_str.c
** File description:
** Task 02 MY_PUTSTR
*/

#include <my.h>

int my_putstr(char const *str)
{
    int i;

    i = 0;
    while (!(str[i] == '\0')) {
        my_putchar(str[i]);
        i++;
    }
}
