/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include "my.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_lists.h"
#include "src.h"

char *format_command(char *c)
{
    char *res = malloc((my_strlen(c) + 1) * sizeof(char));
    int i = 0;
    for (; c[i] ; i++) {
        if (c[i] != '\t') {
            res[i] = c[i];
        } else
            res[i] = ' ';
    }
    if (res[i - 1] == '\n') res[i - 1] = '\0';
    if (!(res[i - 1] == '\n')) res[i] = '\0';
    char *res2 = malloc(sizeof(char) * (my_strlen(res) + 1));
    int k = 0, j = 0;
    while (res[j] == ' ') j++;
    for (; res[j] ; j++) {
        res2[k] = res[j];
        k++;
    }
    free(res);
    res2[k] = '\0';
    return res2;
}

dlist_t *get_semicolon(char *argv)
{
    dlist_t *semicolon = dlist_create();
    char *token = strtok(argv, ";");
    while (token) {
        dlist_pushlast(semicolon, token);
        token = strtok(NULL, ";");
    }
    return semicolon;
}

int main(int argc, char *argv[], char **env)
{
    udata_t *udata = malloc(sizeof(udata_t));
    udata->env = str_array_to_dlist(env);
    udata->run = true;
    udata->old_pwd = NULL;
    char *line = NULL;
    size_t size = 0;
    while (udata->run) {
        if (isatty(STDIN_FILENO)) print_prompt();
        if (getline(&line, &size, stdin) == -1) exit(0);
        dlist_t *semicolons = get_semicolon(line);
        for (node_t *cur = semicolons->head; cur; cur = cur->next) {
            exec(format_command(cur->data), udata);
        }
    }
    return (0);
}
