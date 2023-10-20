#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 3922
#define MAX_ID_LENGTH 20
#define MAX_LINE_LENGTH 200
#define MAX_FILENAME_LENGTH 50
#define LOG_FILENAME "808360_shellsort.txt"

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

void shellSort(Player arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Player temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].height > temp.height; j -= gap) {
                arr[j] = arr[j - gap];
                comparisons++;
                movements++;
            }
            arr[j] = temp;
            movements++;
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

    // Ignorando a primeira linha
    fgets(line, sizeof(line), file);

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
    shellSort(selectedPlayers, inputCount);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;

    writeLog(comparisons, movements, time_taken);

    for (int i = 0; i < inputCount; i++) {
        printf("[Id %d Player %s height %d weight %d born %s collage %s birth city %s birth state %s]\n",
               selectedPlayers[i].id, selectedPlayers[i].playerName, selectedPlayers[i].height,
               selectedPlayers[i].weight, selectedPlayers[i].born, selectedPlayers[i].college,
               selectedPlayers[i].birthCity, selectedPlayers[i].birthState);
    }

    return 0;
}
