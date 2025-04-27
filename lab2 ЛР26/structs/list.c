#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4

void list_init(list *lst) {
    lst->elements = malloc(INITIAL_CAPACITY * sizeof(data_type));
    lst->size = 0;
    lst->capacity = INITIAL_CAPACITY;
}

void list_swap(list *lst, size_t i, size_t j) {
    if (i >= lst->size || j >= lst->size) return;
    data_type temp = lst->elements[i];
    lst->elements[i] = lst->elements[j];
    lst->elements[j] = temp;
}

void list_destroy(list *lst) {
    free(lst->elements);
}

bool list_is_empty(const list *lst) {
    return lst->size == 0;
}

void list_resize(list *lst) {
    if (lst->size < lst->capacity) return;
    lst->capacity *= 2;
    lst->elements = realloc(lst->elements, lst->capacity * sizeof(data_type));
}

void list_push_front(list *lst, data_type data) {
    list_resize(lst);
    for (size_t i = lst->size; i > 0; i--) {
        lst->elements[i] = lst->elements[i-1];
    }
    lst->elements[0] = data;
    lst->size++;
}

void list_push_back(list *lst, data_type data) {
    list_resize(lst);
    lst->elements[lst->size++] = data;
}

void list_pop_front(list *lst) {
    if (list_is_empty(lst)) return;
    for (size_t i = 0; i < lst->size - 1; i++) {
        lst->elements[i] = lst->elements[i+1];
    }
    lst->size--;
}

void list_pop_back(list *lst) {
    if (!list_is_empty(lst)) {
        lst->size--;
    }
}

void list_print(const list *lst) {
    for (size_t i = 0; i < lst->size; i++) {
        printf("(%d, %d) ", lst->elements[i].key, lst->elements[i].value);
    }
    printf("\n");
}

size_t list_size(const list *lst) {
    return lst->size;
}

void list_insert(list *lst, data_type data) {
    list_push_back(lst, data);
}

void list_erase(list *lst, key_type key) {
    for (size_t i = 0; i < lst->size; i++) {
        if (lst->elements[i].key == key) {
            // Сдвигаем элементы влево
            for (size_t j = i; j < lst->size - 1; j++) {
                lst->elements[j] = lst->elements[j+1];
            }
            lst->size--;
            return; 
        }
    }
}

data_type list_get(const list *lst, size_t index) {
    if (index >= lst->size) {
        exit(EXIT_FAILURE);
    }
    return lst->elements[index];
}