#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 3922
#define MAX_ID_LENGTH 10
#define MAX_LINE_LENGTH 200

typedef struct {
    char id[MAX_ID_LENGTH];
    char player[100];
    int height;
    int weight;
    char collage[100];
    char born[50];
    char birth_city[100];
    char birth_state[50];
} Player;

// Shell sort algorithm
void shellSort(Player arr[], int n, unsigned long int *comparisons, unsigned long int *swaps) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Player temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap].height > temp.height; j -= gap) {
                (*comparisons)++;
                arr[j] = arr[j - gap];
                (*swaps)++;
            }
            arr[j] = temp;
        }
    }
}

int main() {
    FILE *inputFile, *outputFile;
    char line[MAX_LINE_LENGTH];
    char filename[] = "/tmp/players.csv";
    char logFilename[] = "808360_shellsort.txt";

    // Abrindo o arquivo de log
    outputFile = fopen(logFilename, "w");
    if (outputFile == NULL) {
        printf("Erro ao criar o arquivo de log.");
        return 1;
    }

    // Registros para o log
    unsigned long int comparisons = 0;
    unsigned long int swaps = 0;
    clock_t begin, end;
    double time_spent;

    // Abrindo o arquivo CSV
    inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        fprintf(outputFile, "Erro ao abrir o arquivo %s\n", filename);
        fclose(outputFile);
        return 1;
    }

    // Lendo os ids e armazenando os jogadores correspondentes
    char id[MAX_ID_LENGTH];
    int count = 0;
    int input_finished = 0;
    Player players[MAX_PLAYERS];

    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        if (strstr(line, "FIM") != NULL) {
            input_finished = 1;
            break;
        }
        if (strstr(line, "Id") == NULL) {
            char *token = strtok(line, ",");
            strcpy(players[count].id, token);

            token = strtok(NULL, ",");
            strcpy(players[count].player, token);

            token = strtok(NULL, ",");
            players[count].height = atoi(token);

            token = strtok(NULL, ",");
            players[count].weight = atoi(token);

            token = strtok(NULL, ",");
            strcpy(players[count].collage, token);

            token = strtok(NULL, ",");
            strcpy(players[count].born, token);

            token = strtok(NULL, ",");
            strcpy(players[count].birth_city, token);

            token = strtok(NULL, ",");
            strcpy(players[count].birth_state, token);

            count++;
        }
    }
    fclose(inputFile);

    // Executando o algoritmo de ordenação
    begin = clock();
    shellSort(players, count, &comparisons, &swaps);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    // Escrevendo no arquivo de log
    fprintf(outputFile, "808360\t%lu\t%lu\t%f\n", comparisons, swaps, time_spent);
    fclose(outputFile);

    // Escrevendo a saída ordenada
    for (int i = 0; i < count; i++) {
        printf("[Id ## %s ## Player ## %s ## height ## %d ## weight ## %d ## born ## %s ## collage ## %s ## birth city ## %s ## birth state ## %s]\n", players[i].id, players[i].player, players[i].height, players[i].weight, players[i].born, players[i].collage, players[i].birth_city, players[i].birth_state);
    }

    return 0;
}
