#include "../structs/list.h"

bool bubble_pass(list *lst, size_t index) {
    if (index + 1 >= list_size(lst)) return false;
    data_type current = list_get(lst, index);
    data_type next = list_get(lst, index + 1);
    bool swapped = false;
    if (current.key > next.key) {
        list_swap(lst, index, index+1); 
        swapped = true;
    }
    return swapped || bubble_pass(lst, index + 1);
}

void bubble_sort(list *lst) {
    if (list_size(lst) <= 1) return;
    if (bubble_pass(lst, 0)) {
        bubble_sort(lst);
    }
}