#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_PLAYERS 3923
#define MAX_ID_LENGTH 10
#define MAX_LINE_LENGTH 200

struct Player {
    int id;
    char name[50];
    int height;
    int weight;
    char born[20];
    char collage[50];
    char birth_city[50];
    char birth_state[50];
};

void bubbleSort(struct Player players[], int n, unsigned long int *comparisons, unsigned long int *swaps) {
    struct Player temp;
    int i, j;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            (*comparisons)++;
            if (players[j].height > players[j+1].height) {
                temp = players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
                (*swaps)++;
            }
        }
    }
}

int main() {
    FILE *inputFile, *logFile;
    char id[MAX_ID_LENGTH];
    char filename[] = "/tmp/players.csv"; 
    char logFilename[] = "808360_bolha.txt";
    char line[MAX_LINE_LENGTH];
    struct Player players[MAX_PLAYERS];
    int count = 0;
    FILE *source, *target;
    char ch;
    source = fopen("players.csv", "r");
    if (source == NULL) {
        printf("Erro ao abrir o arquivo players.csv.\n");
        exit(EXIT_FAILURE);
    }
    target = fopen(filename, "w");
    if (target == NULL) {
        fclose(source);
        printf("Erro ao criar o arquivo em /tmp/players.csv.\n");
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, target);
    }
    fclose(source);
    fclose(target);
    inputFile = fopen(filename, "r");
    if (!inputFile) {
        printf("Erro ao abrir o arquivo em /tmp/players.csv.\n");
        return 1;
    }

    fgets(line, sizeof(line), inputFile);

    while (fgets(line, sizeof(line), inputFile)) {
        sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%[^,],%[^,],%[^\n]", id, players[count].name, &players[count].height, &players[count].weight, players[count].collage, players[count].born, players[count].birth_city, players[count].birth_state);
        players[count].id = atoi(id);
        count++;
    }
    fclose(inputFile);

    unsigned long int comparisons = 0, swaps = 0;
    clock_t begin = clock();
    bubbleSort(players, count, &comparisons, &swaps);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    char outputFilename[] = "/tmp/players_sorted.csv";
    FILE *outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }
    for (int i = 0; i < count; i++) {
        fprintf(outputFile, "[%d ## %s ## %d ## %d ## %s ## %s ## %s ## %s]\n",
                players[i].id, players[i].name, players[i].height, players[i].weight, players[i].born, players[i].collage, players[i].birth_city, players[i].birth_state);
    }
    fclose(outputFile);

    logFile = fopen(logFilename, "w");
    if (!logFile) {
        printf("Erro ao criar o arquivo de log.\n");
        return 1;
    }
    fprintf(logFile, "%d\t%lu\t%lu\t%f", 808360, comparisons, swaps, time_spent);
    fclose(logFile);

    return 0;
}
