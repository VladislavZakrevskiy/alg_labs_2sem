#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <stddef.h> 

typedef int key_type;
typedef int value_type;

typedef struct {
    key_type key;
    value_type value;
} data_type;

typedef struct {
    data_type *elements;
    size_t size;
    size_t capacity;
} list;

// Добавляем объявления функций
void list_init(list *lst);
void list_destroy(list *lst);
bool list_is_empty(const list *lst);
void list_push_front(list *lst, data_type data);
void list_push_back(list *lst, data_type data);
void list_swap(list *lst, size_t i, size_t j);
void list_pop_front(list *lst);
void list_pop_back(list *lst);
void list_print(const list *lst);
size_t list_size(const list *lst);
void list_insert(list *lst, data_type data);
void list_erase(list *lst, key_type key);
data_type list_get(const list *lst, size_t index);

#endif