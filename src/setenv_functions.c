/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell1-louis.chedru
** File description:
** setenv_functions
*/

#include "my.h"
#include "linked_lists.h"
#include <stdlib.h>
#include <string.h>
#include "src.h"

char *make_new_var(dlist_t *args)
{
    int key_size = my_strlen(args->head->next->data);
    int val_size = my_strlen(args->head->next->next->data);
    char *new_var = malloc(sizeof(char) * (key_size + val_size + 2));
    int k = 0;
    for (int i = 0 ; args->head->next->data[i] ; i++) {
        new_var[k] = args->head->next->data[i];
        k++;
    }
    new_var[k] = '=';
    k++;
    for (int j = 0 ; args->head->next->next->data[j] ; j++) {
        new_var[k] = args->head->next->next->data[j];
        k++;
    }
    new_var[k] = 0;
    return new_var;
}

int does_exist(dlist_t *env, char *args)
{
    bool does_already_exist = false;
    int index;
    dlist_t *copy = dlist_create();
    dlist_cpy(env, copy);
    node_t *current = copy->head;
    for (; current && !does_already_exist ; current = current->next) {
        if (my_strcmp(strtok(current->data, "="), args)) {
            does_already_exist = true;
            index = current->index;
        }
    }
    if (does_already_exist) return index;
    if (!does_already_exist) return -1;
}

bool is_char_alphanum(char c)
{
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c >= '0' && c <= '9') return true;
    return false;
}

bool is_var_name_valid(char *name)
{
    if (!is_char_alphanum(name[0])) {
        put_error("setenv", "Variable name must begin with a letter.");
        return false;
    }
    char *msg = "Variable name must contain alphanumeric characters.";
    for (int i = 0 ; name[i] ; i++) {
        if (!is_char_alphanum(name[i])) {
            put_error("setenv", msg);
            return false;
        }
    }
    return true;
}
