// TRABALHO 05 ICC2 (adenilso)
// usa o perfil "337" no thanos com o "few values" que ajuda

#include <stdio.h>
#include <stdlib.h>

// função pra copiar os elementos do vetor lido pra um temp (sub vetor) que vai ser ordenado
void vetorfracionado (int f, int vet[], int temp[]) {

    for (int i = 0; i < f+1; i++) {
        temp[i] = vet[i];
    }
}

// shell do ads
// as alterações do arquivo q ele soltou vão estar marcadas com "#"
void shell(int v[], int n, int *op) { // #
    *op = 0; // #
    int gap = 1;
    while(gap <= n) {
        gap *= 2;
    }
    gap = gap / 2 - 1;
    while(gap > 0) {
        for (int i = gap; i < n; i++){
            int x = v[i]; // uma op
            (*op)++; // #
            int j = i - gap;
            while(v[j] > x && j >= 0) { // uma op, # (inverteu a ordem)
                v[j + gap] = v[j]; // uma op
                j -= gap;
                (*op) = (*op) + 2; // #
            }
            if (j >= 0) // #
                (*op)++; // #
            v[j + gap] = x; // uma op
            (*op)++; // #
        }
        gap /= 2;
    }
}

// quick do ads
// as alterações do arquivo q ele soltou vão estar marcadas com "#"
void quick(int v[], int f, int l, int *op) { // #
    if (f >= l) {
        return;
    }
    int m = (l + f)/2;
    int pivot = v[m]; // uma op
    int i = f;
    int j = l;
    (*op)++; // #
    while(1) {
        while(v[i] < pivot) {
            i++;
            (*op)++; // uma op
        }
        while(v[j] > pivot) {
            j--;
            (*op)++; // uma op
        }
        (*op) = (*op) + 2; // #

        if (i >= j) {
            break;
        }
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
        i++;
        j--;
        (*op) = (*op) + 3; // #
    }
    quick(v, f, j, op);
    quick(v, j+1, l, op);
}

int main() {
    // ler o tamanho e os elementos do vetor X
    int N;
    scanf("%d", &N);
    int *vet;
    vet = (int *) malloc(N*sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &vet[i]);

    // bloco de teste pra garantir que tá lendo certo
//    for (int j = 0; j < N; j++)
//        printf("%d ", vet[j]);
//    printf("\n");

    // cada incremento do for é pra ser um subvetor diferente
    for (int i = 0; i < N; i++) {

        // cria ele onde vai ser guardado o subvetor que vai ser ordenado pelo quick e pelo shell
        int *tempS;
        tempS = (int *) malloc((i+1)*sizeof(int));
        vetorfracionado(i, vet, tempS);
        int *tempQ;
        tempQ = (int *) malloc((i+1)*sizeof(int));
        // olha ali em cima
        vetorfracionado(i, vet, tempQ);

        // bloco de teste pra garantir que tá sendo um elemento "a mais" de cada vez certinho
//        for (int j = 0; j < i+1; j++)
//            printf("%d ", tempS[j]);
//        printf("\n");

        // variavel pra salvar a qtd de operações, ja ordena o vet logo em sequida
        int opQ = 0;
        quick(tempQ, 0, i, &opQ);

        // bloco de texto pra ver se o quick tá ordenando
//        printf("quicj: ");
//        for (int j = 0; j < i+1; j++)
//            printf("%d-%d ", tempQ[j], opQ);
//        printf("\n");

        // variavel pra salvar a qtd de operações, ja ordena o vet logo em sequida
        int opS = 0;
        shell(tempS, i+1, &opS);

        // bloco de texto pra ver se o shell tá ordenando
//        printf("shell: ");
//        for (int j = 0; j < i+1; j++)
//            printf("%d-%d ", tempS[j], opS);
//        printf("\n");

        // print noq o ads quer
        if (opQ < opS)
            printf("Q");
        else if (opQ > opS)
            printf("S");
        else
            printf("-");

        // já da free de uma vez logo
        free(tempS);
        free(tempQ);
    }

    // free no vetor ai
    free(vet);

    return 0;
}