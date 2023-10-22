#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 3922
#define MAX_ID_LENGTH 20
#define MAX_LINE_LENGTH 200
#define MAX_FILENAME_LENGTH 50
#define LOG_FILENAME "808360_partialinsertionsort.txt"
#define K 10

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

void insertionSort(Player arr[], int n) {
    for (int i = 1; i < n; i++) {
        Player key = arr[i];
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j].born, key.born) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
            comparisons++;
            movements++;
        }
        arr[j + 1] = key;
        movements++;
    }
}

void partialInsertionSort(Player arr[], int n) {
    for (int i = 0; i < n; i += K) {
        if (i + K <= n) {
            insertionSort(arr + i, K);
        } else {
            insertionSort(arr + i, n - i);
        }
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

    int inputId;
    int inputIds[464];
    int inputCount = 0;
    while (scanf("%d", &inputId)) {
        if (inputId == -1) {
            break;
        }
        inputIds[inputCount] = inputId;
        inputCount++;
    }

    Player selectedPlayers[inputCount];
    for (int i = 0; i < inputCount; i++) {
        for (int j = 0; j < count; j++) {
            if (players[j].id == inputIds[i]) {
                selectedPlayers[i] = players[j];
            }
        }
    }

    clock_t t;
    t = clock();
    partialInsertionSort(selectedPlayers, inputCount);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;

    writeLog(comparisons, movements, time_taken);

    for (int i = 0; i < inputCount; i++) {
        printf("[Id ## %d Player ## %s height ## %d weight ## %d born ## %s collage ## %s birth city ## %s birth state ## %s]\n",
               selectedPlayers[i].id, selectedPlayers[i].playerName, selectedPlayers[i].height,
               selectedPlayers[i].weight, selectedPlayers[i].born, selectedPlayers[i].college,
               selectedPlayers[i].birthCity, selectedPlayers[i].birthState);
    }

    return 0;
}
