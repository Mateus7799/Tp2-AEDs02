#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 3922
#define MAX_ID_LENGTH 20
#define MAX_LINE_LENGTH 200
#define MAX_FILENAME_LENGTH 50
#define LOG_FILENAME "808360_heapsort.txt"
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

void swap(Player *a, Player *b) {
    Player t = *a;
    *a = *b;
    *b = t;
}

void heapify(Player arr[], int n, int i) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l].height > arr[smallest].height) {
        smallest = l;
    }

    if (r < n && arr[r].height > arr[smallest].height) {
        smallest = r;
    }

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        heapify(arr, n, smallest);
    }
}

void heapSort(Player arr[], int n) {
    for (int i = K / 2 - 1; i >= 0; i--) {
        heapify(arr, K, i);
    }

    for (int i = K; i < n; i++) {
        if (arr[i].height < arr[0].height) {
            swap(&arr[i], &arr[0]);
            heapify(arr, K, 0);
        }
    }

    for (int i = K - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
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

    Player smallestPlayers[K];
    for (int i = 0; i < K; i++) {
        smallestPlayers[i] = players[i];
    }

    clock_t t;
    t = clock();
    heapSort(smallestPlayers, K);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;

    writeLog(comparisons, movements, time_taken);

    for (int i = 0; i < K; i++) {
        printf("[Id ## %d Player ## %s height ## %d weight ## %d born ## %s collage ## %s birth city ## %s birth state ## %s]\n",
               smallestPlayers[i].id, smallestPlayers[i].playerName, smallestPlayers[i].height,
               smallestPlayers[i].weight, smallestPlayers[i].born, smallestPlayers[i].college,
               smallestPlayers[i].birthCity, smallestPlayers[i].birthState);
    }

    return 0;
}
