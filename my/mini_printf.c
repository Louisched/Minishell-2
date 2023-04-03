/*
** EPITECH PROJECT, 2022
** mini_printf.c
** File description:
** mini_printf
*/

#include "my.h"
#include <stdarg.h>

int is_in_list(char c)
{
    char list[] = "csid%";
    for (int i = 0 ; list[i] != '\0' ; i++)
        if (c == list[i])
            return (1);
    return (0);
}

int mini_printf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    for (int i = 0 ; format[i] != '\0' ; i++) {
        if (format[i] == '%' && is_in_list(format[i + 1]) == 1) {
            (format[i + 1] == 'c') ? my_putchar(va_arg(ap, int)) : 0;
            (format[i + 1] == 's') ? my_putstr(va_arg(ap, char *)) : 0;
            (format[i + 1] == 'i') ? my_put_nbr(va_arg(ap, int)) : 0;
            (format[i + 1] == 'd') ? my_put_nbr(va_arg(ap, int)) : 0;
            (format[i + 1] == '%') ? my_putchar('%') : 0;
            i++;
        } else
            my_putchar(format[i]);
    }
    va_end(ap);
    return (0);
}
