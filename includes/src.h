/*
** EPITECH PROJECT, 2022
** functions
** File description:
** functions
*/

#include "linked_lists.h"
#include <stdbool.h>

#ifndef FUNCTIONS_H_
    #define FUNCTIONS_H_

    typedef struct {
        dlist_t *env;
        char *old_pwd;
        bool run;
    } udata_t;

    typedef struct {
        enum {REDIR_R, REDIR_L, REDIR_RDB} type;
        int fd;
    } redirect_t;

    dlist_t *str_array_to_dlist(char **array);
    char **dlist_to_str_array(dlist_t *list);
    int exec(char *argv, udata_t *udata);
    void put_error(char *err_src, char *error);
    void put_simple_error(char *error);
    char *get_valid_bin_path(dlist_t *env, char *command);
    void prepare_cmd(char **cmd, dlist_t *env);
    void add_at_beginning(char **command, char *to_add);
    int does_exist(dlist_t *env, char *args);
    char *get_env_var_content(char *var, dlist_t *env);
    char *format_command(char *c);
    bool cd_home(dlist_t *args, int *value, dlist_t *env);
    bool cd_error_handling(dlist_t *args);
    bool cd_dash_and_other(dlist_t *args, char **old_pwd, int *value);
    char *put_point(char *str);
    bool cd_chdir_error(int *value, dlist_t *args);
    int change_env_var_content(char *var, char *data, dlist_t *env);
    char *make_new_var(dlist_t *args);
    bool is_var_name_valid(char *name);
    void handle_builtins(char *command, bool *running, dlist_t *env,
    char **oldp_wd);
    bool is_command_builtin(char *c);
    char **separate_command(char *c);
    redirect_t *get_redirections(char *cmd);
    char *get_currdir(void);

    int my_cd(dlist_t *args, dlist_t *env, char **old_pwd);
    int my_exit(bool *running);
    int my_env(dlist_t *env);
    int my_setenv(dlist_t *env, dlist_t *args);
    int my_unsetenv(dlist_t *args, dlist_t *env);
    void print_prompt(void);
    bool is_only_space(char *str);

    #define PROMPT "\x1B[35m\e[1m\e[3mMysh\e[0m\x1B[0m \x1B[34m➜ \e[0m"

#endif /* !FUNCTIONS_H_ */
