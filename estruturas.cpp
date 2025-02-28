#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <stdbool.h>

// Função para gerar números aleatórios
int* numerosAleatorios(int N, int d) {
    int* x = (int*)malloc(sizeof(int) * N);
    if (x == NULL) {
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    for (int i = 0; i < N; i++) {
        x[i] = rand() % (d * N) + 1;
    }
    return x;
}

// Função para ler dados do arquivo
int* lerDados(int t) {
    FILE *f = fopen("numerosAleatorios.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }
    int* res = (int*)malloc(t * sizeof(int));
    if (res == NULL) {
        printf("Erro ao alocar memória!\n");
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < t; i++) {
        fscanf(f, "%d", &res[i]);
    }
    fclose(f);
    return res;
}

// Função para gerar números aleatórios e salvar em um arquivo
void gerarNumerosAleatorios(int t) {
    FILE *f = fopen("numerosAleatorios.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    int dispersao = 100;
    srand(100); // Semente fixa para reproducibilidade
    int* res = numerosAleatorios(t, dispersao);
    if (res == NULL) {
        fclose(f);
        return;
    }
    for (int i = 0; i < t; i++) {
        fprintf(f, "%d\n", res[i]);
    }
    fclose(f);
    free(res); // Libera a memória alocada
}

// Função para mostrar valores (apenas para debug)
void mostrarValores(int *x, int t) {
    for (int i = 0; i < t; i++) {
        printf("x[%d] = %d\n", i, x[i]);
    }
}

// Função de ordenação SelectionSort
void SelectionSort(int *x, int n) {
    for (int i = 0; i < n; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            if (x[j] < x[menor]) {
                menor = j;
            }
        }
        int temp = x[i];
        x[i] = x[menor];
        x[menor] = temp;
    }
}

// Função de ordenação BubbleSort
void bubbleSort(int *x, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (x[j] > x[j + 1]) {
                int temp = x[j];
                x[j] = x[j + 1];
                x[j + 1] = temp;
            }
        }
    }
}

// Função de ordenação QuickSort
void quicksort(int *x, int ini, int fim) {
    if (ini >= fim) return;
    int pivo = x[(ini + fim) / 2];
    int i = ini, j = fim;
    while (i <= j) {
        while (x[i] < pivo) i++;
        while (x[j] > pivo) j--;
        if (i <= j) {
            int temp = x[i];
            x[i] = x[j];
            x[j] = temp;
            i++;
            j--;
        }
    }
    quicksort(x, ini, j);
    quicksort(x, i, fim);
}

// Função de ordenação MergeSort
void merge(int *x, int inf, int sup, int mid) {
    int i = inf, j = mid + 1, k = 0;
    int *temp = (int*)malloc((sup - inf + 1) * sizeof(int));
    if (temp == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    while (i <= mid && j <= sup) {
        if (x[i] < x[j]) {
            temp[k++] = x[i++];
        } else {
            temp[k++] = x[j++];
        }
    }
    while (i <= mid) temp[k++] = x[i++];
    while (j <= sup) temp[k++] = x[j++];
    for (i = inf, k = 0; i <= sup; i++, k++) {
        x[i] = temp[k];
    }
    free(temp);
}

void mergeSort(int *x, int inf, int sup) {
    if (inf < sup) {
        int mid = (inf + sup) / 2;
        mergeSort(x, inf, mid);
        mergeSort(x, mid + 1, sup);
        merge(x, inf, sup, mid);
    }
}

// Função de ordenação BucketSort
void BucketSort(int *x, int n) {
    int max_val = x[0];
    for (int i = 1; i < n; i++) {
        if (x[i] > max_val) {
            max_val = x[i];
        }
    }
    int* count = (int*)calloc(max_val + 1, sizeof(int));
    if (count == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        count[x[i]]++;
    }
    int index = 0;
    for (int i = 0; i <= max_val; i++) {
        while (count[i] > 0) {
            x[index++] = i;
            count[i]--;
        }
    }
    free(count);
}

// Função de ordenação GnomeSort
void GnomeSort(int *x, int size) {
    int i = 0;
    while (i < size) {
        if (i == 0 || x[i - 1] <= x[i]) {
            i++;
        } else {
            int temp = x[i];
            x[i] = x[i - 1];
            x[i - 1] = temp;
            i--;
        }
    }
}

// Função de ordenação ShellSort
void ShellSort(int *x, int n) {
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i++) {
            int temp = x[i];
            int j;
            for (j = i; j >= interval && x[j - interval] > temp; j -= interval) {
                x[j] = x[j - interval];
            }
            x[j] = temp;
        }
    }
}

// Função para calcular o tempo em segundos
float tempo(clock_t tempo) {
    return ((float)tempo) / CLOCKS_PER_SEC;
}

// Função principal
int main(void) {
    int vSize = 100;
    int vIncrement = 10;
    int tentativa = 5;
    FILE *result = fopen("tempos.txt", "w");
    if (result == NULL) {
        printf("Erro ao abrir o arquivo tempos.txt!\n");
        return 1;
    }

    int *v = (int*)malloc(vSize * sizeof(int));
    if (v == NULL) {
        printf("Erro ao alocar memória!\n");
        fclose(result);
        return 1;
    }

    for (int i = 0; i < vSize; i++) {
        v[i] = vIncrement * (i + 1);
    }

    for (int j = 0; j < vSize; j++) {
        gerarNumerosAleatorios(v[j]);
        int *x = (int*)malloc(v[j] * sizeof(int));
        if (x == NULL) {
            printf("Erro ao alocar memória!\n");
            free(v);
            fclose(result);
            return 1;
        }

        clock_t dB[tentativa], dQ[tentativa], dM[tentativa], dBucket[tentativa], dSele[tentativa], dGnome[tentativa], dShell[tentativa];

        for (int i = 0; i < tentativa; i++) {
            // BubbleSort
            x = lerDados(v[j]);
            dB[i] = clock();
            bubbleSort(x, v[j]);
            dB[i] = clock() - dB[i];

            // QuickSort
            x = lerDados(v[j]);
            dQ[i] = clock();
            quicksort(x, 0, v[j] - 1);
            dQ[i] = clock() - dQ[i];

            // MergeSort
            x = lerDados(v[j]);
            dM[i] = clock();
            mergeSort(x, 0, v[j] - 1);
            dM[i] = clock() - dM[i];

            // BucketSort
            x = lerDados(v[j]);
            dBucket[i] = clock();
            BucketSort(x, v[j]);
            dBucket[i] = clock() - dBucket[i];

            // SelectionSort
            x = lerDados(v[j]);
            dSele[i] = clock();
            SelectionSort(x, v[j]);
            dSele[i] = clock() - dSele[i];

            // GnomeSort
            x = lerDados(v[j]);
            dGnome[i] = clock();
            GnomeSort(x, v[j]);
            dGnome[i] = clock() - dGnome[i];

            // ShellSort
            x = lerDados(v[j]);
            dShell[i] = clock();
            ShellSort(x, v[j]);
            dShell[i] = clock() - dShell[i];
        }

        // Calcula a média dos tempos
        clock_t sB = 0, sQ = 0, sM = 0, sBucket = 0, sSele = 0, sGnome = 0, sShell = 0;
        for (int i = 0; i < tentativa; i++) {
            sB += dB[i];
            sQ += dQ[i];
            sM += dM[i];
            sBucket += dBucket[i];
            sSele += dSele[i];
            sGnome += dGnome[i];
            sShell += dShell[i];
        }
        sB /= tentativa;
        sQ /= tentativa;
        sM /= tentativa;
        sBucket /= tentativa;
        sSele /= tentativa;
        sGnome /= tentativa;
        sShell /= tentativa;

        // Salva os tempos no arquivo
        fprintf(result, "%i\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", v[j], tempo(sB), tempo(sQ), tempo(sM), tempo(sBucket), tempo(sSele), tempo(sGnome), tempo(sShell));

        free(x); // Libera a memória alocada para x
    }

    free(v); // Libera a memória alocada para v
    fclose(result); // Fecha o arquivo de resultados
    return 0;
}
