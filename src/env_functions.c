/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell1-louis.chedru
** File description:
** env_functions
*/

#include "my.h"
#include "src.h"
#include "linked_lists.h"
#include <stdlib.h>
#include <string.h>

char **copy_env(char **env)
{
    int i = 0;
    while (env[i]) i++;
    char **copy = malloc(i * sizeof(char *));
    for (int j = 0 ; env[j] ; j++) {
        copy[j] = malloc((1 + my_strlen(env[j])) * sizeof(char));
        my_strcpy(env[j], copy[j]);
    }
    return copy;
}

dlist_t *str_array_to_dlist(char **array)
{
    dlist_t *list = dlist_create();
    for (int i = 0 ; array[i] ; i++)
        dlist_pushlast(list, array[i]);
    return list;
}

char **dlist_to_str_array(dlist_t *list)
{
    char **res = malloc(sizeof(char *) * (list->length + 1));
    node_t *current = list->head;
    int i = 0;
    for (; current ; current = current->next) {
        res[i] = malloc(sizeof(char) * (my_strlen(current->data) + 1));
        my_strcpy(current->data, res[i]);
        i++;
    }
    res[i] = NULL;
    return res;
}

char *get_env_var_content(char *var, dlist_t *env)
{
    dlist_t *cpy = dlist_create();
    dlist_cpy(env, cpy);
    node_t *current = cpy->head;
    char *res;
    for (; current ; current = current->next) {
        if (my_strcmp(strtok(current->data, "="), var)) {
            return strtok(NULL, "=");
        }
    }
    return NULL;
}

int change_env_var_content(char *var, char *data, dlist_t *env)
{
    int index = 0;
    char *d_cpy = malloc(sizeof(char) * (my_strlen(var) + 2));
    my_strcpy(var, d_cpy);
    d_cpy[my_strlen(var)] = '=';
    d_cpy[my_strlen(var) + 1] = '\0';
    index = does_exist(env, var);
    if (index == -1) return -1;
    node_t *to_modify = dlist_getnode(env, index);
    free(to_modify->data);
    add_at_beginning(&data, d_cpy);
    to_modify->data = malloc(sizeof(char) * (my_strlen(data) + 1));
    my_strcpy(data, to_modify->data);
    return 0;
}
