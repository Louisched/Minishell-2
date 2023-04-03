/*
** EPITECH PROJECT, 2023
** B-PSU-200-MLN-2-1-minishell2-louis.chedru
** File description:
** prompt
*/

#include "src.h"
#include "my.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char *get_currdir(void)
{
    char buff[4096];
    for (int i = 0 ; i < 4096 ; i++) buff[i] = '\0';
    char *cwd = getcwd(buff, 4096);
    char *token = strtok(cwd, "/");
    char *final = NULL;
    while (token) {
        final = my_strndup(token, 0);
        token = strtok(NULL, "/");
    }
    return final;
}

char *my_strcat(char *s1, char *s2)
{
    int size = my_strlen(s2) + my_strlen(s2) + 1;
    char *res = malloc(sizeof(char) * size);
    int i = 0;
    for (; s1[i]; i++) res[i] = s1[i];
    for (int j = 0 ; s2[j]; j++, i++) res[i] = s2[j];
    res[i] = '\0';
    return res;
}

void print_prompt(void)
{
    my_putstr("╭─\x1B[35m\e[1m\e[3mMysh\e[0m\x1B[0m \x1B[34m❯ \e[0m");
    my_putstr("\e[1m\x1B[34m");
    my_putstr(get_currdir());
    my_putstr(" \e[0m\n╰─➤ ");
}
