#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 3923
#define FILENAME "../tmp/players.csv"
#define LOG_FILENAME "808360_bolha.txt"

void BubbleSort(Log* log, Lista lista) {
    int N = lista.size;
    Jogador* array = lista.array;
    int comparisons = 0, swaps = 0;

    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - 1; j++) {
            comparisons++;
            if (lista.CompareToInt(array[j], array[j + 1], log)) {
                swap(&array[j], &array[j + 1], log);
                swaps++;
            }
        }
    }

    log->comparisons = comparisons;
    log->swaps = swaps;
}

int main() {
    Timer timer = newTimer();
    Log log;
    log.comparisons = 0;
    log.swaps = 0;
    Lista BD = newLista(MAX_PLAYERS);
    BD.ImportDataBase(FILENAME, &BD);

    Lista lista = newLista(465); 
    char inputPUBIN[STR_MAX_LEN];

    while (strcmp(readStr(0, inputPUBIN), "FIM")) {
        int id = atoi(inputPUBIN);
        lista.Inserir(BD.Get(id, BD), &lista);
        lista.setAtributo(&BD.array[id].anoNascimento, lista);
    }

    timer.Start(&timer);
    BubbleSort(&log, lista);
    timer.Stop(&timer);

    lista.Mostrar(lista);

    FILE *logFile = fopen(LOG_FILENAME, "w");
    if (!logFile) {
        printf("Erro ao criar o arquivo de log.\n");
        return 1;
    }
    fprintf(logFile, "%d\t%d\t%d\t%f", 808360, log.comparisons, log.swaps, timer.totalTime);
    fclose(logFile);

    lista.Close(&lista);
    BD.Close(&BD);
}
