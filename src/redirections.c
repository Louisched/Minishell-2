/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-bsminishell2-louis.chedru
** File description:
** redirections
*/

#include "src.h"
#include "my.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>

char *get_file_name(char *cmd, int index)
{
    char *file_name = my_strndup(cmd, index + 1);
    char *token = strtok(file_name, " \n");
    return token;
}

redirect_t *do_redirection(int type, int i, char *cmd)
{
    redirect_t *redir = malloc(sizeof(redirect_t));
    int open_flags = 0;
    redir->type = type;
    switch (type) {
    case REDIR_R:
        open_flags = O_WRONLY | O_CREAT | O_TRUNC;
        break;
    case REDIR_L:
        open_flags = O_RDONLY;
        break;
    case REDIR_RDB:
        open_flags = O_WRONLY | O_APPEND | O_CREAT;
        break;
    }
    redir->fd = open(get_file_name(cmd, i), open_flags, 0666);
    return redir;
}

redirect_t *get_redirections(char *cmd)
{
    redirect_t *redirect = malloc(sizeof(redirect_t));
    bool found = false;
    for (int i = 0 ; cmd[i] && !found ; i++) {
        if (cmd[i] == '>' && cmd[i + 1] != '>')
            return do_redirection(REDIR_R, i, cmd);
        if (cmd[i] == '<')
            return do_redirection(REDIR_L, i, cmd);
        if (cmd[i] == '>' && cmd[i + 1] == '>')
            return do_redirection(REDIR_RDB, i + 1, cmd);
    }
    return NULL;
}
