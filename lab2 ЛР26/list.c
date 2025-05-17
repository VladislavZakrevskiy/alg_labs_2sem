#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void list_init(list* lst) {
    lst->head = NULL;
    lst->size = 0;
}

void list_push_back(list* lst, key_type key) {
    node* n = (node*)malloc(sizeof(node));
    n->key = key;
    n->next = NULL;
    if (!lst->head) {
        lst->head = n;
    } else {
        node* cur = lst->head;
        while (cur->next) cur = cur->next;
        cur->next = n;
    }
    lst->size++;
}

size_t list_size(const list* lst) {
    return lst->size;
}

// Возвращает value_type с .key полем
value_type list_get(const list* lst, size_t idx) {
    value_type v = {0};
    if (idx >= lst->size) return v;
    node* cur = lst->head;
    size_t i = 0;
    while (cur && i < idx) {
        cur = cur->next;
        i++;
    }
    if (cur) v.key = cur->key;
    return v;
}

// Пузырьковая сортировка (меняем только key, не указатели!)
void list_bubble_sort(list* lst) {
    if (!lst->head) return;
    for (size_t out = 0; out < lst->size; ++out) {
        node* cur = lst->head;
        node* next = cur ? cur->next : NULL;
        for (size_t in = 0; in < lst->size - 1 - out && next; ++in) {
            if (cur->key > next->key) {
                key_type tmp = cur->key;
                cur->key = next->key;
                next->key = tmp;
            }
            cur = next;
            next = cur->next;
        }
    }
}

void list_free(list* lst) {
    node* cur = lst->head;
    while (cur) {
        node* tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    lst->head = NULL;
    lst->size = 0;
}

void list_print(const list *lst) {
    printf("[");
    node* cur = lst->head;
    while (cur) {
        printf("%d", cur->key);
        if (cur->next) printf(",");
        cur = cur->next;
    }
    printf("]\n");
}

void plot_data(const list *lst, const char *title) {
    printf("\033[1;34m%s\033[0m\n", title);
    
    size_t size = list_size(lst);
    if (size == 0) {
        printf("Список пуст\n");
        return;
    }

    key_type max_key = list_get(lst, 0).key;
    for (size_t i = 1; i < size; i++) {
        if (list_get(lst, i).key > max_key) {
            max_key = list_get(lst, i).key;
        }
    }

    for (int y = max_key; y >= 0; y--) {
        printf("%4d |", y);
        for (size_t x = 0; x < size; x++) {
            key_type key = list_get(lst, x).key;
            if (key >= y) {
                if (x % 2 == 0) printf("\033[32m#\033[0m");
                else printf("\033[31m#\033[0m");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("      ");
    for (size_t i = 0; i < size; i++) printf("--");
    printf("\n");
}
