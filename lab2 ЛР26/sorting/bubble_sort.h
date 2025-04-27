#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

#include "../structs/list.h"
#include <stdio.h>  

bool bubble_pass(list *lst, size_t index);
void bubble_sort(list *lst);

#endif