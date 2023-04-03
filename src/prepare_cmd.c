/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-bsminishell2-louis.chedru
** File description:
** prepare_cmd
*/

#include "src.h"
#include <stdlib.h>

char *make_copy(char *command, char *to_add)
{
    int ta_size = my_strlen(to_add);
    int p_size = my_strlen(command);
    char *copy = malloc(sizeof(char) * (ta_size + p_size + 1));
    int i = 0, k = 0;
    while (to_add[i]) {
        copy[i] = to_add[i];
        i++;
    }
    while (command[k]) {
        copy[i] = command[k];
        i++;
        k++;
    }
    copy[i] = 0;
    return copy;
}

bool must_add(char *arg)
{
    if (arg[0] == '/') return false;
    if (my_strlen(arg) > 1)
        if (arg[0] == '.' && arg[1] == '/') return false;
    if (my_strlen(arg) > 2)
        if (arg[0] == '.' && arg[1] == '.' && arg[2] == '/') return false;
    return true;
}

void add_at_beginning(char **command, char *to_add)
{
    char *copy = make_copy(*command, to_add);
    *command = malloc(sizeof(char) * (my_strlen(copy) + 1));
    my_strcpy(copy, *command);
}

void prepare_cmd(char **cmd, dlist_t *env)
{
    char *bin_path = get_valid_bin_path(env, *cmd);
    if (must_add(*cmd) && bin_path) {
        add_at_beginning(cmd, bin_path);
    }
}
