#include "list.h"
#include <stdio.h>

int main() {
    list lst;
    list_init(&lst);

    printf("Введите числа (через пробел или перевод строки, Ctrl+D для конца ввода):\n");
    key_type x;
    while (scanf("%d", &x) == 1) {
        list_push_back(&lst, x);
    }

    list_print(&lst);
    plot_data(&lst, "До сортировки:");

    list_bubble_sort(&lst);

    list_print(&lst);
    plot_data(&lst, "После пузырьковой сортировки:");

    list_free(&lst);
    return 0;
}
