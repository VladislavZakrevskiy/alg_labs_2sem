#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char team1[35];
    char team2[35];
    char tournament[35];
    int score1;
    int score2;
} match;

int to_bin(const char *input_name, const char *output_name);
int from_bin(const char *input_name);
int stat_score(const char *input_name);

int is_empty_line(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) return 0;
        line++;
    }
    return 1;
}

void print_help() {
    printf("Доступные команды:\n");
    printf("to_bin <input> <output>  - Конвертировать текстовый файл в бинарный\n");
    printf("from_bin <input>         - Показать содержимое бинарного файла\n");
    printf("stats <input>            - Статистика матчей с разными счетами\n");
    printf("exit                     - Выйти из программы\n");
}

int main() {
    char command[256];
    char *args[4];
    int running = 1;

    printf("=== Введите команду (help для списка команд) ===\n");
    
    while (running) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) == NULL) break;

        command[strcspn(command, "\n")] = '\0';

        int argc = 0;
        char *token = strtok(command, " ");
        while (token != NULL && argc < 4) {
            args[argc++] = token;
            token = strtok(NULL, " ");
        }

        if (argc == 0) continue;

        if (strcmp(args[0], "help") == 0) {
            print_help();
        } else if (strcmp(args[0], "exit") == 0) {
            running = 0;
        } else if (strcmp(args[0], "to_bin") == 0) {
            if (argc != 3) {
                fprintf(stderr, "Ошибка: требуется 2 аргумента\n");
            } else {
                to_bin(args[1], args[2]);
            }
        } else if (strcmp(args[0], "from_bin") == 0) {
            if (argc != 2) {
                fprintf(stderr, "Ошибка: требуется 1 аргумент\n");
            } else {
                from_bin(args[1]);
            }
        } else if (strcmp(args[0], "stats") == 0) {
            if (argc != 2) {
                fprintf(stderr, "Ошибка: требуется 1 аргумент\n");
            } else {
                stats(args[1]);
            }
        } else {
            fprintf(stderr, "Неизвестная команда: %s\n", args[0]);
        }
    }

    return 0;
}

int to_bin(const char *input_name, const char *output_name) {
    match m;
    FILE *file1 = fopen(input_name, "r");
    if (!file1) {
        perror("Ошибка открытия входного файла");
        return -1;
    }

    FILE *file2 = fopen(output_name, "wb");
    if (!file2) {
        perror("Ошибка открытия выходного файла");
        fclose(file1);
        return -1;
    }

    char line[256];
    int line_num = 0;
    while (fgets(line, sizeof(line), file1)) {
        line_num++;
        line[strcspn(line, "\n")] = '\0';

        if (is_empty_line(line)) {
            fprintf(stderr, "\nПредупреждение: пустая строка %d\n\n", line_num);
            continue;
        }

 
        int colons = 0;
        for (char *p = line; *p; p++) if (*p == ':') colons++;
        if (colons != 4) {
            fprintf(stderr, "\nОшибка в строке %d: неверное количество полей\n\n", line_num);
            continue;
        }

        match m;
        int parsed = sscanf(line, "%34[^:]:%34[^:]:%34[^:]:%d:%d", 
                           m.team1, m.team2, m.tournament, &m.score1, &m.score2);
        if (parsed != 5) {
            fprintf(stderr, "\nОшибка в строке %d: некорректные данные\n\n", line_num);
            continue;
        }

        printf("%s:%s:%s:%d:%d\n", 
            m.team1, m.team2, m.tournament, m.score1, m.score2);
        memset(m.team1 + strlen(m.team1), 0, 35 - strlen(m.team1));
        memset(m.team2 + strlen(m.team2), 0, 35 - strlen(m.team2));
        memset(m.tournament + strlen(m.tournament), 0, 35 - strlen(m.tournament));
        fwrite(&m, sizeof(match), 1, file2);
    }

    fclose(file1);
    fclose(file2);
    return 0;
}

int from_bin(const char *input_name) {
    match m;
    FILE *binFile = fopen(input_name, "rb");
    if (!binFile) {
        perror("Ошибка открытия файла");
        return -1;
    }

    while (fread(&m, sizeof(match), 1, binFile) == 1) {
        m.team1[34] = '\0';
        m.team2[34] = '\0';
        m.tournament[34] = '\0';
        printf("%s:%s:%s:%d:%d\n", m.team1, m.team2, m.tournament, m.score1, m.score2);
    }

    if (!feof(binFile)) {
        perror("Ошибка чтения файла");
    }

    fclose(binFile);
    return 0;
}

int stats(const char *input_name) {
    match m;
    FILE *binFile = fopen(input_name, "rb");
    if (!binFile) {
        perror("Ошибка открытия файла");
        return -1;
    }
    int two_zero = 0, one_two=0;
    while (fread(&m, sizeof(match), 1, binFile) == 1) {
        m.team1[34] = '\0';
        m.team2[34] = '\0';
        m.tournament[34] = '\0';
        if (m.score1 == 0 || m.score2 == 0){
            two_zero++;
        }
        else{
            one_two++;
        }
    }
    printf("Количество матчей со счетом 2:0  :   %d\nКоличество матчей со счетом 2:1  :   %d\n", two_zero, one_two);

    if (!feof(binFile)) {
        perror("Ошибка чтения файла");
    }

    fclose(binFile);
    return 0;
}