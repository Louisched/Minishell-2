/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell1-louis.chedru
** File description:
** put_error
*/

#include <unistd.h>
#include "my.h"

void put_error(char *err_src, char *error)
{
    int i = 0;
    for (; err_src[i] ; i++) write(2, &err_src[i], 1);
    write(2, ": ", 2);
    int j = 0;
    for (; error[j] ; j++) write(2, &error[j], 1);
    write(2, "\n", 1);
}

void put_simple_error(char *error)
{
    for (int i = 0 ; error[i] ; i++) write(2, &error[i], 1);
    write(2, "\n", 1);
}
