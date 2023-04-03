/*
** EPITECH PROJECT, 2022
** Linked lists
** File description:
** Jeader for linked lists
*/

#include "../includes/my.h"

#ifndef LINKED_LISTS_H_
    #define LINKED_LISTS_H_

    typedef struct node {
        char *data;
        int fdarr[2];
        int index;
        struct node *next;
        struct node *prev;
    } node_t;

    typedef struct Dlist {
        int length;
        node_t *head;
        node_t *tail;
    }dlist_t;

    dlist_t *dlist_create(void);
    int dlist_len(dlist_t *list);
    void dlist_pushlast(dlist_t *list, char *to_add);
    void dlist_display(dlist_t *list, char *separator);
    node_t *dlist_pop(dlist_t **list, int index);
    node_t *dlist_getnode(dlist_t *list, int index);
    void dlist_nodecpy(node_t *to_copy, node_t *dest);
    void dlist_cpy(dlist_t *src, dlist_t *dest);
    void dlist_empty(dlist_t **list);
    void dlist_pushfirst(dlist_t *list, char *to_add);
    void dlist_pushmid(dlist_t *list, char *to_add, int index);

#endif /* !LINKED_LISTS_H_ */
