/*
** EPITECH PROJECT, 2022
** str append
** File description:
** Append data to a str linked list
*/

#include <stdlib.h>
#include "linked_lists.h"
#include "my.h"

dlist_t *dlist_create(void)
{
    dlist_t *list = malloc(sizeof(dlist_t));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    return list;
}

void dlist_pushlast(dlist_t *list, char *to_add)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = malloc(sizeof(char) * (my_strlen(to_add) + 1));
    my_strcpy(to_add, new_node->data);
    if (list->head == NULL && list->tail == NULL) {
        new_node->prev = NULL;
        new_node->next = NULL;
        new_node->index = 0;
        list->head = new_node;
        list->tail = new_node;
    } else {
        new_node->index = list->tail->index + 1;
        list->tail->next = new_node;
        new_node->prev = list->tail;
        new_node->next = NULL;
        list->tail = new_node;
    }
    list->length++;
}

void dlist_display(dlist_t *list, char *separator)
{
    node_t *current = list->head;
    while (current != NULL) {
        my_put_nbr(current->index);
        my_putchar(':');
        my_putstr(current->data);
        if (current->index < list->length - 1) my_putstr(separator);
        current = current->next;
    }
    my_putchar('\n');
}

void dlist_nodecpy(node_t *to_copy, node_t *dest)
{
    dest->data = to_copy->data;
    dest->index = to_copy->index;
    dest->prev = NULL;
    dest->next = NULL;
}

node_t *dlist_pop(dlist_t **list, int index)
{
    if (index >= (* list)->length) return NULL;
    node_t *current = (* list)->head;
    node_t *to_return = malloc(sizeof(node_t));
    if (index == 0) {
        dlist_nodecpy(current, to_return);
        (* list)->head = current->next;
    }
    if (index > 0) {
        while (current->next->index < index) current = current->next;
        dlist_nodecpy(current, to_return);
        current->next = current->next->next;
    }
    while (current->next != NULL) {
        current->next->index--;
        current = current->next;
    }
    (* list)->length--;
    if ((* list)->length == 0) (* list)->head = NULL;
    if ((* list)->length == 0) (* list)->tail = NULL;
    return to_return;
}
