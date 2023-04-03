/*
** EPITECH PROJECT, 2022
** dlist functions
** File description:
** File B for dlist functions
*/

#include <stdlib.h>
#include "src.h"
#include "linked_lists.h"
#include "my.h"
#include <stdbool.h>

node_t *dlist_getnode(dlist_t *list, int index)
{
    if (index >= list->length) return NULL;
    if (index == 0) return list->head;
    node_t *current = list->head;
    while (current->next->index < index) current = current->next;
    return current->next;
}

void dlist_cpy(dlist_t *src, dlist_t *dest)
{
    node_t *current = src->head;
    while (current != NULL) {
        dlist_pushlast(dest, current->data);
        current = current->next;
    }
}

void dlist_empty(dlist_t **list)
{
    if ((* list)->length == 0) return;
    if ((* list)->length == 1) {
        free((* list)->head);
        free((* list)->tail);
        (* list)->length = 0;
        (* list)->head = NULL;
        (* list)->tail = NULL;
        return;
    }
    node_t *current = (* list)->head;
    current = current->next;
    while (current != NULL) {
        free(current->prev);
        current = current->next;
    }
    (* list)->length = 0;
    free((* list)->tail);
    (* list)->head = NULL;
    (* list)->tail = NULL;
    free(*list);
}

void dlist_pushfirst(dlist_t *list, char *to_add)
{
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = malloc((my_strlen(to_add) + 1) * sizeof(char));
    my_strcpy(to_add, new_node->data);
    new_node->index = 0;
    list->length++;
    if (list->head == NULL && list->tail == NULL) {
        new_node->next = NULL;
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;
        return;
    }
    new_node->next = list->head;
    new_node->prev = NULL;
    list->head->prev = new_node;
    list->head = new_node;
    node_t *current = list->head->next;
    for (; current ; current = current->next)
        current->index++;
}

void dlist_pushmid(dlist_t *list, char *to_add, int index)
{
    if (index > list->length) return;
    if (index == list->length) return dlist_pushlast(list, to_add);
    if (index == 0) return dlist_pushfirst(list, to_add);
    node_t *new_node = malloc(sizeof(node_t));
    new_node->data = malloc((my_strlen(to_add) + 1) * sizeof(char));
    my_strcpy(to_add, new_node->data);
    new_node->index = index;
    node_t *current = list->head;
    while (current->next->index < index) current = current->next;
    new_node->next = current->next;
    new_node->prev = dlist_getnode(list, current->index);
    current->next = new_node;
    current = new_node;
    while (current->next != NULL) {
        current->next->index++;
        current = current->next;
    }
    list->length++;
}
