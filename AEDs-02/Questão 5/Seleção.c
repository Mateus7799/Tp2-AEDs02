#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 3922
#define MAX_ID_LENGTH 20
#define MAX_LINE_LENGTH 200
#define MAX_FILENAME_LENGTH 50
#define LOG_FILENAME "808360_selecao.txt"

typedef struct {
    int id;
    char playerName[100];
    int height;
    int weight;
    char born[50];
    char college[100];
    char birthCity[50];
    char birthState[50];
} Player;

int comparisons = 0;
int movements = 0;

void writeLog(int comparisons, int movements, double time_taken) {
    FILE *logFile = fopen(LOG_FILENAME, "w");
    if (logFile == NULL) {
        printf("Erro ao criar o arquivo de log.");
        return;
    }
    fprintf(logFile, "808360\t%d\t%d\t%f", comparisons, movements, time_taken);
    fclose(logFile);
}

void selectionSort(Player arr[], int n) {
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (strcmp(arr[j].playerName, arr[min_idx].playerName) < 0) {
                min_idx = j;
            }
            comparisons++;
        }
        Player temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
        movements += 3;
    }
}

int main() {
    FILE *file;
    char filename[MAX_FILENAME_LENGTH] = "/tmp/players.csv";
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.");
        return 1;
    }

    Player players[MAX_PLAYERS];
    char line[MAX_LINE_LENGTH];

    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (count >= MAX_PLAYERS) {
            break;
        }
        sscanf(line, "%d,%[^,],%d,%d,%[^,],%[^,],%[^,],%s",
               &players[count].id, players[count].playerName, &players[count].height,
               &players[count].weight, players[count].college, players[count].born,
               players[count].birthCity, players[count].birthState);
        count++;
    }
    fclose(file);

    clock_t t;
    t = clock();
    selectionSort(players, count);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;

    writeLog(comparisons, movements, time_taken);

    for (int i = 0; i < count; i++) {
        printf("[Id ## %d Player ## %s height ## %d weight ## %d born ## %s collage ## %s birth city ## %s birth state ## %s]\n",
               players[i].id, players[i].playerName, players[i].height,
               players[i].weight, players[i].born, players[i].college,
               players[i].birthCity, players[i].birthState);
    }

    return 0;
}
