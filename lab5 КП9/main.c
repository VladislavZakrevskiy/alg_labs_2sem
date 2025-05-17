#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_RECORDS 19
#define MAX_TEXT 128

typedef struct {
    long long part1;
    long long part2;
} ComplexKey;

typedef struct {
    ComplexKey key;
    char text[MAX_TEXT];
} Record;

int compare_keys(const ComplexKey *a, const ComplexKey *b) {
    if (a->part1 < b->part1) return -1;
    if (a->part1 > b->part1) return 1;
    if (a->part2 < b->part2) return -1;
    if (a->part2 > b->part2) return 1;
    return 0;
}

void print_record(const Record *rec) {
    printf("Key: (%lld,%lld), Text: %s\n", rec->key.part1, rec->key.part2, rec->text);
}

void print_records(const Record arr[], int n, const char *title) {
    printf("=== %s ===\n", title);
    for (int i = 0; i < n; i++)
        print_record(&arr[i]);
    printf("\n");
}

void selection_sort(Record arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (compare_keys(&arr[j].key, &arr[min_idx].key) < 0)
                min_idx = j;
        }
        if (min_idx != i) {
            Record tmp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = tmp;
        }
    }
}

int binary_search(const Record arr[], int n, const ComplexKey *key) {
    int left = 0, right = n-1;
    while (left <= right) {
        int mid = (left + right)/2;
        int cmp = compare_keys(&arr[mid].key, key);
        if (cmp == 0)
            return mid;
        if (cmp < 0)
            left = mid + 1;
        else
            right = mid -1;
    }
    return -1;
}

ComplexKey random_key() {
    ComplexKey k;
    k.part1 = rand() % 2000 - 1000;
    k.part2 = rand() % 2000 - 1000;
    return k;
}

void input_records(Record arr[], int n, int mode) {
    const char *poem[] = {
        "У лукоморья дуб зелёный;",
        "Златая цепь на дубе том;",
        "И днём и ночью кот учёный",
        "Всё ходит по цепи кругом;",
        "Идёт направо — песнь заводит,",
        "Налево — сказку говорит.",
        "Там чудеса: там леший бродит,",
        "Русалка на ветвях сидит;",
        "Там на неведомых дорожках",
        "Следы невиданных зверей;",
        "Избушка там на курьих ножках",
        "Стоит без окон, без дверей;",
        "Там лес и дол видений полны;",
        "Там о заре прихлынут волны",
        "На брег песчаный и пустой,",
        "И тридцать витязей прекрасных",
        "Чредой из вод выходят ясных,",
        "И с ними дядька их морской;",
        "Там королевич мимоходом"
    };

    for (int i = 0; i < n; ++i) {
        arr[i].key.part1 = i;
        arr[i].key.part2 = 2*i;
        strncpy(arr[i].text, poem[i % (sizeof(poem)/sizeof(poem[0]))], MAX_TEXT-1);
        arr[i].text[MAX_TEXT-1] = 0;
    }
    if (mode == 2) { 
        for (int i = 0; i < n; ++i) {
            arr[i].key.part1 = n-i-1;
            arr[i].key.part2 = 2*(n-i-1);
        }
    } else if (mode == 3) { 
        for (int i = 0; i < n; ++i) {
            arr[i].key = random_key();
        }
    }
}

void prompt_key(ComplexKey *key) {
    printf("Введите ключ (две целых части через пробел): ");
    scanf("%lld %lld", &key->part1, &key->part2);
}

int main() {
    Record table[MAX_RECORDS];
    srand(time(NULL));
    int n = MAX_RECORDS;

    input_records(table, n, 1);
    print_records(table, n, "Исходная таблица (отсортирована)");
    selection_sort(table, n);
    print_records(table, n, "После сортировки (отсортирована)");

    input_records(table, n, 2);
    print_records(table, n, "Исходная таблица (обратный порядок)");
    selection_sort(table, n);
    print_records(table, n, "После сортировки (обратный порядок)");

    input_records(table, n, 3);
    print_records(table, n, "Исходная таблица (случайный порядок)");
    selection_sort(table, n);
    print_records(table, n, "После сортировки (случайный порядок)");

    printf("Выполнена сортировка. Введите ключи для поиска (две целых через пробел, конец ввода Ctrl+D):\n");
    ComplexKey search_key;
    while (printf("> "), fflush(stdout), scanf("%lld %lld", &search_key.part1, &search_key.part2) == 2) {
        int idx = binary_search(table, n, &search_key);
        if (idx != -1) {
            printf("Найдено: ");
            print_record(&table[idx]);
        } else {
            printf("Элемент с таким ключом не найден.\n");
        }
    }

    return 0;
}

