/*
** EPITECH PROJECT, 2023
** bootstrap
** File description:
** my_strcpy
*/

void my_strcpy(char *src, char *dest)
{
    int i = 0;
    for (; src[i] ; i++) dest[i] = src[i];
    dest[i] = '\0';
}
