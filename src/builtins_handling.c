/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-bsminishell2-louis.chedru
** File description:
** builtins_handling
*/

#include "src.h"
#include "linked_lists.h"
#include <stdbool.h>
#include "my.h"
#include <stdlib.h>
#include <string.h>

bool is_command_builtin(char *c)
{
    int i = 0;
    char *cpy = malloc((my_strlen(c) + 1) * sizeof(char));
    my_strcpy(c, cpy);
    char *word = strtok(cpy, " ");
    bool value = false;
    if (my_strcmp(word, "cd") && !value) value = true;
    if (my_strcmp(word, "setenv") && !value) value = true;
    if (my_strcmp(word, "unsetenv") && !value) value = true;
    if (my_strcmp(word, "env") && !value) value = true;
    if (my_strcmp(word, "exit") && !value) value = true;
    free(cpy);
    return value;
}

void handle_builtins(char *command, bool *running, dlist_t *env,
                    char **oldp_wd)
{
    dlist_t *argv = dlist_create();
    char *arg = strtok(command, " ");
    while (arg) {
        dlist_pushlast(argv, arg);
        arg = strtok(NULL, " ");
    }
    if (my_strcmp(argv->head->data, "cd")) my_cd(argv, env, oldp_wd);
    if (my_strcmp(argv->head->data, "exit")) my_exit(running);
    if (my_strcmp(argv->head->data, "env")) my_env(env);
    if (my_strcmp(argv->head->data, "setenv")) my_setenv(env, argv);
    if (my_strcmp(argv->head->data, "unsetenv")) my_unsetenv(argv, env);
}
