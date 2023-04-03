/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell2-louis.chedru
** File description:
** errors
*/

#include "my.h"

bool is_only_space(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] != ' ') return false;
    }
    return true;
}
