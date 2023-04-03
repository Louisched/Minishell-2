/*
** EPITECH PROJECT, 2022
** my_putnbr.c
** File description:
** My_putnbr
*/

#include "my.h"

int my_put_nbr(int nb)
{
    if (nb >= 0 && nb < 10)
        my_putchar(nb + 48);
    if (nb < 0) {
        my_putchar('-');
        my_put_nbr(-nb);
    }
    if (nb >= 10) {
        my_put_nbr(nb / 10);
        my_put_nbr(nb % 10);
    }
}
