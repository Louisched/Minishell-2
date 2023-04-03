/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-bsminishell2-louis.chedru
** File description:
** separate_cmd
*/

#include "linked_lists.h"
#include <string.h>
#include "src.h"

char **separate_command(char *c)
{
    dlist_t *args = dlist_create();
    char *token = strtok(c, " ");
    while (token) {
        dlist_pushlast(args, token);
        token = strtok(NULL, " ");
    }
    return dlist_to_str_array(args);
}
