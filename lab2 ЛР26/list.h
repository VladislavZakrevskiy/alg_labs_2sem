#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef int key_type;

typedef struct {
    key_type key;
} value_type;

typedef struct node {
    key_type key;
    struct node* next;
} node;

typedef struct list {
    node* head;
    size_t size;
} list;

void list_init(list* lst);
void list_push_back(list* lst, key_type key);
size_t list_size(const list* lst);
void list_print(const list *lst);
value_type list_get(const list* lst, size_t idx);
void list_bubble_sort(list* lst);
void list_free(list* lst);

// График
void plot_data(const list *lst, const char *title);

#endif
