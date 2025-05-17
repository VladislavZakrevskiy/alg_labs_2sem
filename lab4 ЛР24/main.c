#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum { NUM, OP } NodeType;

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define BLUE    "\x1B[34m"
#define GRAY    "\x1B[90m"
    
typedef struct Node {
    NodeType type;
    union {
        double val;
        struct {
            char op;
            struct Node *left, *right;
        } opr;
    };
} Node;

Node* new_num(double x) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = NUM;
    n->val = x;
    return n;
}

Node* new_op(char op, Node* left, Node* right) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->type = OP;
    n->opr.op = op;
    n->opr.left = left;
    n->opr.right = right;
    return n;
}

void free_tree(Node* t) {
    if (!t) return;
    if (t->type == OP) {
        free_tree(t->opr.left);
        free_tree(t->opr.right);
    }
    free(t);
}

int prio(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        default: return 0;
    }
}

Node* parse_expr(const char* s) {
    const char* p = s;
    Node *valstk[128];
    int vn = 0;
    char opstk[128];
    int on = 0;

    while (*p) {
        if (isspace(*p)) { p++; continue; }
        if (isdigit(*p) || *p=='.') {
            double x;
            char* q;
            x = strtod(p, &q);
            valstk[vn++] = new_num(x);
            p = q;
        } else if (*p=='(') {
            opstk[on++] = '(';
            p++;
        } else if (*p==')') {
            while (on && opstk[on-1]!='(') {
                char op = opstk[--on];
                Node *r = valstk[--vn];
                Node *l = valstk[--vn];
                valstk[vn++] = new_op(op, l, r);
            }
            if (on && opstk[on-1]=='(') --on;
            p++;
        } else if (strchr("+-*/", *p)) {
            char op = *p;
            while (on && prio(opstk[on-1]) >= prio(op)) {
                char op2 = opstk[--on];
                Node *r = valstk[--vn];
                Node *l = valstk[--vn];
                valstk[vn++] = new_op(op2, l, r);
            }
            opstk[on++] = op;
            p++;
        } else {
            printf("Ошибка: неизвестный символ: %c\n", *p);
            exit(1);
        }
    }
    while (on) {
        char op = opstk[--on];
        Node *r = valstk[--vn];
        Node *l = valstk[--vn];
        valstk[vn++] = new_op(op, l, r);
    }
    return valstk[0];
}

void print_tree_nice(Node* node, char *prefix, int is_left) {
    if (!node) return;

    printf("%s", prefix);
    printf(is_left ? "├── " : "└── ");

    if (node->type == OP)
        printf(BLUE "%c" RESET "\n", node->opr.op);
    else
        printf(RED "%.2lf" RESET "\n", node->val);

    char new_prefix[256];
    strcpy(new_prefix, prefix);
    strcat(new_prefix, is_left ? "│   " : "    ");

    int childrens = 0;
    if (node->type == OP) {
        if (node->opr.left) childrens++;
        if (node->opr.right) childrens++;
    }

    if (node->type == OP) {
        if (node->opr.left && node->opr.right) {
            print_tree_nice(node->opr.left, new_prefix, 1);
            print_tree_nice(node->opr.right, new_prefix, 0);
        } else if (node->opr.left) {
            print_tree_nice(node->opr.left, new_prefix, 0);
        } else if (node->opr.right) {
            print_tree_nice(node->opr.right, new_prefix, 0);
        }
    }
}


void print_expr(Node* t) {
    if (!t) return;
    if (t->type == NUM)
        printf("%.2lf", t->val);
    else {
        int bracket_left = (t->opr.left->type == OP && prio(t->opr.left->opr.op) < prio(t->opr.op));
        int bracket_right = (t->opr.right->type == OP &&
                             ((prio(t->opr.right->opr.op) < prio(t->opr.op)) ||
                              (prio(t->opr.right->opr.op) == prio(t->opr.op) && (t->opr.op == '-'))));
        if (bracket_left) printf("(");
        print_expr(t->opr.left);
        if (bracket_left) printf(")");
        printf(" %c ", t->opr.op);
        if (bracket_right) printf("(");
        print_expr(t->opr.right);
        if (bracket_right) printf(")");
    }
}

Node* remove_zero_summands(Node* t) {
    if (!t) return NULL;
    if (t->type == NUM)
        return new_num(t->val);

    Node* l = remove_zero_summands(t->opr.left);
    Node* r = remove_zero_summands(t->opr.right);

    if (t->opr.op == '+') {
        if (l->type == NUM && fabs(l->val) < 1e-10) {
            free_tree(l);
            return r;
        }
        if (r->type == NUM && fabs(r->val) < 1e-10) {
            free_tree(r);
            return l;
        }
    }
    Node* node = new_op(t->opr.op, l, r);
    return node;
}

int main() {
    char buf[256];
    printf("Введите выражение: ");
    if (!fgets(buf, sizeof(buf), stdin)) return 1;
    buf[strcspn(buf, "\n")] = 0;

    printf("Исходное выражение: %s\n", buf);
    Node* t = parse_expr(buf);

    printf("Исходное дерево:\n");
    print_tree_nice(t, "", 0);


    printf("Исходное выражение (сгенерировано из дерева): ");
    print_expr(t);
    printf("\n");

    Node* t2 = remove_zero_summands(t);

    printf("\nПреобразованное дерево:\n");
    print_tree_nice(t2, "", 0);

    printf("Преобразованное выражение: ");
    print_expr(t2);
    printf("\n");

    free_tree(t);   
    free_tree(t2);  

    return 0;
}
