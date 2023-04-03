/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell1-louis.chedru
** File description:
** cd_functions
*/

#include "my.h"
#include "src.h"
#include "linked_lists.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

bool cd_home(dlist_t *args, int *value, dlist_t *env)
{
    if (args->length == 1) {
        *value = chdir(get_env_var_content("HOME", env));
        return true;
    } else if (my_strcmp(args->head->next->data, "~")) {
        *value = chdir(get_env_var_content("HOME", env));
        return true;
    }
    return false;
}

bool cd_error_handling(dlist_t *args)
{
    if (args->length > 2) {
        write(2, "cd: Too many arguments\n", 24);
        return true;
    }
    return false;
}

bool cd_dash_and_other(dlist_t *args, char **old_pwd, int *value)
{
    if (args->length == 2) {
        if (my_strcmp(args->head->next->data, "-")) {
            *value = chdir(*old_pwd);
            return true;
        }
        if (!my_strcmp(args->head->next->data, "-")) {
            *value = chdir(args->head->next->data);
            return true;
        }
    }
    return false;
}

char *put_point(char *str)
{
    char *res = malloc(sizeof(char) * (my_strlen(str) + 2));
    int i = 0;
    for (; str[i] ; i++) res[i] = str[i];
    res[i] = '.';
    res[i + 1] = '\0';
    return res;
}

bool cd_chdir_error(int *value, dlist_t *args)
{
    if (*value == -1) {
        put_error(args->head->next->data, put_point(strerror(errno)));
        return true;
    }
    return false;
}
