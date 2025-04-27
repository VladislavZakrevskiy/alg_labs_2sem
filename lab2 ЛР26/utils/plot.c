#include "../structs/list.h"
#include <stdio.h>  

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