#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define GRAY    "\x1B[90m"

typedef struct Node {
    float value;
    struct Node* parent;
    struct Node* first_child;
    struct Node* next_sibling;
} Node;

typedef struct {
    int max_depth;
    Node* result_node;
} MaxDepthInfo;

Node* create_node(float value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->value = value;
    new_node->parent = NULL;
    new_node->first_child = NULL;
    new_node->next_sibling = NULL;
    return new_node;
}

void add_child(Node* parent, Node* new_node) {
    new_node->parent = parent;
    if (parent->first_child == NULL) {
        parent->first_child = new_node;
    } else {
        Node* sibling = parent->first_child;
        while (sibling->next_sibling != NULL) {
            sibling = sibling->next_sibling;
        }
        sibling->next_sibling = new_node;
    }
}

void free_tree(Node* node) {
    if (node == NULL) return;
    Node* child = node->first_child;
    while (child != NULL) {
        Node* next = child->next_sibling;
        free_tree(child);
        child = next;
    }
    free(node);
}

Node* find_node(Node* root, float value) {
    if (root == NULL) return NULL;
    if (root->value == value) return root;
    Node* child = root->first_child;
    while (child != NULL) {
        Node* found = find_node(child, value);
        if (found != NULL) return found;
        child = child->next_sibling;
    }
    return NULL;
}

void print_tree(Node* node, bool* levels, int level, bool is_last) {
    if (node == NULL) return;

    for (int i = 0; i < level - 1; i++) {
        if (levels[i]) {
            printf(GRAY "│   " RESET);
        } else {
            printf("    ");
        }
    }

    if (level > 0) {
        printf(GRAY);
        if (is_last) {
            printf("└──" RESET);
        } else {
            printf("├──" RESET);
        }
    }

    if (node->first_child == NULL) {
        printf(RED);
    } else if (node->parent == NULL) {
        printf(GREEN);
    } else {
        printf(BLUE);
    }
    printf(" %.2f" RESET "\n", node->value);

    if (level > 0) {
        levels[level - 1] = !is_last;
    }

    Node* child = node->first_child;
    int child_count = 0;
    for (Node* tmp = child; tmp != NULL; tmp = tmp->next_sibling) {
        child_count++;
    }

    int current_child = 0;
    bool new_levels[level + 1];
    memcpy(new_levels, levels, level * sizeof(bool));
    new_levels[level] = false;

    while (child != NULL) {
        current_child++;
        print_tree(child, new_levels, level + 1, current_child == child_count);
        child = child->next_sibling;
    }
}

void delete_node(Node** root, float value) {
    if (*root == NULL) return;

    Node* target;
    if ((*root)->value == value) {
        target = *root;
        *root = NULL;
    } else {
        target = find_node(*root, value);
        if (target == NULL) {
            printf(RED "Узел не найден.\n" RESET);
            return;
        }

        Node* parent = target->parent;
        if (parent->first_child == target) {
            parent->first_child = target->next_sibling;
        } else {
            Node* sibling = parent->first_child;
            while (sibling->next_sibling != target) {
                sibling = sibling->next_sibling;
            }
            sibling->next_sibling = target->next_sibling;
        }
    }

    free_tree(target);
}

void find_max_depth_non_terminal(Node* node, int current_depth, MaxDepthInfo* info) {
    if (node == NULL) return;

    if (node->first_child != NULL) {
        if (current_depth > info->max_depth) {
            info->max_depth = current_depth;
            info->result_node = node;
        } else if (current_depth == info->max_depth && info->result_node == NULL) {
            info->result_node = node;
        }
    }

    Node* child = node->first_child;
    while (child != NULL) {
        find_max_depth_non_terminal(child, current_depth + 1, info);
        child = child->next_sibling;
    }
}

int main() {
    Node* root = NULL;
    int choice;
    do {
        printf("\033[H\033[J");
        
        printf("\n" GREEN "Меню:" RESET "\n");
        printf("1. Добавить узел\n");
        printf("2. Вывести дерево\n");
        printf("3. Удалить узел\n");
        printf("4. Вычислить функцию\n");
        printf("5. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        while (getchar() != '\n');

        switch (choice) {
            case 1: {
                printf("\n=== Добавление узла ===\n");
                if (root == NULL) {
                    float value;
                    printf("Введите значение корня: ");
                    scanf("%f", &value);
                    root = create_node(value);
                    printf(GREEN "Корень создан.\n" RESET);
                } else {
                    float parent_value, new_value;
                    printf("Введите значение родительского узла: ");
                    scanf("%f", &parent_value);
                    printf("Введите значение нового узла: ");
                    scanf("%f", &new_value);
                    Node* parent = find_node(root, parent_value);
                    if (parent == NULL) {
                        printf(RED "Родитель не найден.\n" RESET);
                    } else {
                        Node* new_node = create_node(new_value);
                        add_child(parent, new_node);
                        printf(GREEN "Узел добавлен.\n" RESET);
                    }
                }
                printf("Нажмите Enter для продолжения...");
                getchar();
                break;
            }
            case 2: {
                printf("\n=== Визуализация дерева ===\n");
                bool levels[100] = {false};
                print_tree(root, levels, 0, true);
                printf("\nНажмите Enter для продолжения...");
                getchar();
                break;
            }
            case 3: {
                printf("\n=== Удаление узла ===\n");
                if (root == NULL) {
                    printf(RED "Дерево пусто.\n" RESET);
                } else {
                    float value;
                    printf("Введите значение узла для удаления: ");
                    scanf("%f", &value);
                    delete_node(&root, value);
                    printf(GREEN "Узел удален.\n" RESET);
                }
                printf("Нажмите Enter для продолжения...");
                getchar();
                break;
            }
            case 4: {
                printf("\n=== Вычисление функции ===\n");
                if (root == NULL) {
                    printf(RED "Дерево пусто.\n" RESET);
                } else {
                    MaxDepthInfo info = { -1, NULL };
                    find_max_depth_non_terminal(root, 0, &info);
                    if (info.result_node != NULL) {
                        printf("Значение нетерминальной вершины с максимальной глубиной: " 
                               BLUE "%.2f" RESET "\n", info.result_node->value);
                    } else {
                        printf("Нет нетерминальных вершин.\n");
                    }
                }
                printf("Нажмите Enter для продолжения...");
                getchar();
                break;
            }
            case 5:
                printf("Выход.\n");
                break;
            default:
                printf(RED "Неверный выбор.\n" RESET);
                printf("Нажмите Enter для продолжения...");
                getchar();
        }
    } while (choice != 5);

    free_tree(root);
    return 0;
}