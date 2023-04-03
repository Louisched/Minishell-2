/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell1-louis.chedru
** File description:
** get_env_var_index
*/

#include "my.h"
#include "linked_lists.h"
#include "src.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

char *get_env_var_index(dlist_t *env, char *var, int index)
{
    char *content = get_env_var_content(var, env);
    if (!content) return NULL;
    char *cont_index = strtok(content, ":");
    for (int i = 0 ; cont_index ; i++) {
        if (i == index) return cont_index;
        cont_index = strtok(NULL, ":");
    }
    return NULL;
}

bool does_file_exist(char *content, char *command)
{
    struct stat st;
    int cont_size = my_strlen(content);
    int c_size = my_strlen(command);
    char *copy = malloc(sizeof(char) * (c_size + cont_size + 3));
    int k = 0, j = 0;
    for (; content[k] ; k++)
        copy[k] = content[k];
    copy[k] = '/';
    k++;
    for (; command[j] ; j++, k++)
        copy[k] = command[j];
    copy[k] = '\0';
    bool return_value = stat(copy, &st) != -1;
    free(copy);
    return return_value;
}

int get_command_size(char *command)
{
    int i = 0;
    while (command[i] != ' ' && command[i] != '\t') i++;
    return i;
}

char *get_valid_bin_path(dlist_t *env, char *command)
{
    char *content = get_env_var_index(env, "PATH", 0), *copy;
    bool found = false;
    char *command_copy = malloc(sizeof(char) * (my_strlen(command) + 1));
    my_strcpy(command, command_copy);
    char *bin = strtok(command_copy, " \t");
    for (int i = 1 ; content && !found ; i++) {
        found = does_file_exist(content, bin);
        if (!found) content = get_env_var_index(env, "PATH", i);
    }
    free(command_copy);
    if (found) {
        char *to_return = malloc(sizeof(char) * (my_strlen(content) + 2));
        int l = 0;
        for (; content[l] ; l++) to_return[l] = content[l];
        to_return[l] = '/';
        to_return[l + 1] = '\0';
        return to_return;
    } else {
        return NULL;
    }
}
