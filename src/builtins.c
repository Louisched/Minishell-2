/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell1-louis.chedru
** File description:
** builtins
*/

#include <unistd.h>
#include <sys/stat.h>
#include "my.h"
#include "src.h"
#include "linked_lists.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int my_cd(dlist_t *args, dlist_t *env, char **old_pwd)
{
    int value;
    char buff[4096];
    if (cd_error_handling(args)) return 1;
    if (!cd_home(args, &value, env)) {
        cd_dash_and_other(args, old_pwd, &value);
        if (cd_chdir_error(&value, args)) return 1;
    }
    *old_pwd = get_env_var_content("PWD", env);
    change_env_var_content("PWD", getcwd(buff, 4096), env);
    return 0;
}

int my_exit(bool *running)
{
    my_putstr("exit\n");
    *running = false;
    return 0;
}

int my_env(dlist_t *env)
{
    node_t *current = env->head;
    for (; current ; current = current->next) {
        mini_printf("%s\n", current->data);
    }
    return 0;
}

int my_setenv(dlist_t *env, dlist_t *args)
{
    if (args->length > 3) return 1;
    if (args->length == 1) return my_env(env);
    if (args->length == 2) dlist_pushlast(args, "");
    if (!is_var_name_valid(args->head->next->data)) return 1;
    char *new_var;
    int index = does_exist(env, args->head->next->data);
    char *var = args->head->next->data;
    if (index != -1) {
        change_env_var_content(var, args->head->next->next->data, env);
    } else {
        new_var = make_new_var(args);
        dlist_pushlast(env, new_var);
    }
    return 0;
}

int my_unsetenv(dlist_t *args, dlist_t *env)
{
    if (args->length < 2) {
        put_error("unsetenv", "Too few arguments.");
        return 1;
    }
    int index = does_exist(env, args->head->next->data);
    if (index != -1) {
        dlist_pop(&env, index);
        return 0;
    } else {
        return 1;
    }
}
