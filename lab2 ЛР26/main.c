#include <stdbool.h>
#include <stdio.h>  
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include "./utils/plot.h"
#include "./structs/list.h"
#include "./sorting/bubble_sort.h"

int random_in_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL)); 
    
    // TEST 1
    printf("Test 1\n");
    clock_t start_1 = clock(); 
    list lst_1;
    list_init(&lst_1);

    data_type d1_1 = {5, 50};
    data_type d2_1 = {3, 30};
    data_type d3_1 = {8, 80};
    data_type d4_1 = {1, 10};
    list_push_back(&lst_1, d1_1);
    list_push_back(&lst_1, d2_1);
    list_push_back(&lst_1, d3_1);
    list_push_back(&lst_1, d4_1);

    printf("Original list: ");
    list_print(&lst_1);
    plot_data(&lst_1, "Original List");

    bubble_sort(&lst_1);

    printf("Sorted list: ");
    list_print(&lst_1);
    plot_data(&lst_1, "Sorted List");

    list_destroy(&lst_1);

    clock_t end_1 = clock(); 
    printf("Количество секунд: %lf сек.\n", (double)(end_1 - start_1) / 1000);

    // TEST 2
    clock_t start_2 = clock(); 
    
    printf("Test 2\n");
    list lst_2;
    list_init(&lst_2);

    data_type d1_2 = {10, 1};
    data_type d2_2 = {31, 1};
    data_type d3_2 = {32, 1};
    data_type d4_2 = {42, 1};
    data_type d5_2 = {23, 1};
    data_type d6_2 = {21, 1};
    data_type d7_2 = {32, 1};
    data_type d8_2 = {43, 1};
    data_type d9_2 = {2, 1};
    data_type d10_2 = {1, 1};
    data_type d11_2 = {33, 1};
    data_type d12_2 = {43, 1};
    data_type d13_2 = {12, 1};
    list_push_back(&lst_2, d1_2);
    list_push_back(&lst_2, d2_2);
    list_push_back(&lst_2, d3_2);
    list_push_back(&lst_2, d4_2);
    list_push_back(&lst_2, d5_2);
    list_push_back(&lst_2, d6_2);
    list_push_back(&lst_2, d7_2);
    list_push_back(&lst_2, d8_2);
    list_push_back(&lst_2, d9_2);
    list_push_back(&lst_2, d10_2);
    list_push_back(&lst_2, d11_2);
    list_push_back(&lst_2, d12_2);
    list_push_back(&lst_2, d13_2);

    printf("Original list: ");
    list_print(&lst_2);
    plot_data(&lst_2, "Original List");

    bubble_sort(&lst_2);

    printf("Sorted list: ");
    list_print(&lst_2);
    plot_data(&lst_2, "Sorted List");

    list_destroy(&lst_2);

    clock_t end_2 = clock();
    printf("Количество секунд: %lf сек.\n", (double)(end_2 - start_2) / 1000);

    // TEST 3
    clock_t start_3 = clock(); 

    printf("Test 3\n");
    list lst_3;
    list_init(&lst_3);

    data_type d1_3 = {1, 1};
    data_type d2_3 = {2, 1};
    data_type d3_3 = {3, 1};
    data_type d4_3 = {4, 1};
    list_push_back(&lst_3, d1_3);
    list_push_back(&lst_3, d2_3);
    list_push_back(&lst_3, d3_3);
    list_push_back(&lst_3, d4_3);

    printf("Original list: ");
    list_print(&lst_3);
    plot_data(&lst_3, "Original List");

    bubble_sort(&lst_3);

    printf("Sorted list: ");
    list_print(&lst_3);
    plot_data(&lst_3, "Sorted List");

    list_destroy(&lst_3);

    clock_t end_3 = clock();
    printf("Количество секунд: %lf сек.\n", (double)(end_3 - start_3) / 1000);

    // TEST 4
    clock_t start_4 = clock(); 

    printf("Test 4\n");
    list lst_4;
    list_init(&lst_4);

    for (int i = 0; i < 50; i++) {
        data_type data = {random_in_range(1, 50), 1};
        list_push_back(&lst_4, data);
    }

    printf("Original list: ");
    list_print(&lst_4);
    plot_data(&lst_4, "Original List");

    bubble_sort(&lst_4);

    printf("Sorted list: ");
    list_print(&lst_4);
    plot_data(&lst_4, "Sorted List");

    list_destroy(&lst_4);

    clock_t end_4 = clock();
    printf("Количество секунд: %lf сек.\n", (double)(end_4 - start_4) / 1000);
    
    return 0;
}