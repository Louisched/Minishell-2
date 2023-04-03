/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-bsminishell2-louis.chedru
** File description:
** exec
*/

#include "src.h"
#include "my.h"
#include "linked_lists.h"
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>

dlist_t *parse_pipes(char *c)
{
    dlist_t *parsed = dlist_create();
    char *token = strtok(c, "|");
    while (token) {
        dlist_pushlast(parsed, token);
        token = strtok(NULL, "|");
    }
    return parsed;
}

void execute_cmd(char *cmd, udata_t *udata)
{
    if (is_command_builtin(cmd)) {
        handle_builtins(cmd, &udata->run, udata->env, &udata->old_pwd);
        exit(0);
    } else {
        char **sep = separate_command(cmd);
        char *dup = malloc((my_strlen(sep[0]) + 1) * sizeof(char));
        my_strcpy(sep[0], dup);
        prepare_cmd(&dup, udata->env);
        execve(dup, sep, dlist_to_str_array(udata->env));
        put_error(strtok(cmd, " "), "Command not found.");
        exit(1);
    }
}

int exec_in_child(node_t *curr, udata_t *udata, int fd, int fdarr[2])
{
    pid_t child = fork();
    if (child == 0) {
        close(fdarr[0]);
        if (curr->next) dup2(fdarr[1], 1);
        dup2(fd, 0);
        execute_cmd(curr->data, udata);
    } else {
        close(fdarr[1]);
        int wstatus = 0;
        wait(&wstatus);
        if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 1) return -1;
        if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGSEGV)
            put_simple_error(strsignal(SIGSEGV));
    }
    return 0;
}

void exec_pipe(node_t *curr, udata_t *udata, int fd)
{
    if (!curr) return;
    if (is_only_space(curr->data)) {
        put_simple_error("Invalid null command.");
        return;
    }
    int fdarr[2];
    pipe(fdarr);
    int ch_status = 0;
    if ((!is_command_builtin(curr->data))
    || (is_command_builtin(curr->data) && curr->next))
        ch_status = exec_in_child(curr, udata, fd, fdarr);
    else if (is_command_builtin(curr->data))
        handle_builtins(curr->data, &udata->run, udata->env, &udata->old_pwd);
    exec_pipe(curr->next, udata, fdarr[0]);
}

int exec(char *argv, udata_t *udata)
{
    if (argv[0] == '|') {
        put_simple_error("Invalid null command.");
        return 1;
    }
    redirect_t *redir = get_redirections(argv);
    int save_fd[2] = {dup(0), dup(1)};
    char *to_execute = strtok(argv, "<>");
    dlist_t *pipes = parse_pipes(to_execute);
    if (redir) {
        if (redir->type == REDIR_R) dup2(redir->fd, 1);
        if (redir->type == REDIR_RDB) dup2(redir->fd, 1);
        if (redir->type == REDIR_L) dup2(redir->fd, 0);
    }
    exec_pipe(pipes->head, udata, 0);
    if (redir) {
        if (redir->type == REDIR_R) dup2(save_fd[1], 1);
        if (redir->type == REDIR_RDB) dup2(save_fd[1], 1);
        if (redir->type == REDIR_L) dup2(save_fd[0], 0);
        close(redir->fd);
    }
}
