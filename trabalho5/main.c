// TRABALHO 05 ICC2 (adenilso)
// usa o perfil "337" no thanos com o "few values" que ajuda
// sobre essa nova versão: a contagem do quick do anterior era sem recursão, essa tá com. e o shell tá retornando tb, ao inves da variavel.

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
int shell(int v[], int n) { // #
    int op = 0; // #
    int gap = 1;
    while(gap <= n) {
        gap *= 2;
    }
    gap = gap / 2 - 1;
    while(gap > 0) {
        for (int i = gap; i < n; i++){
            int x = v[i]; // uma op
            op++; // #
            int j = i - gap;
            while(v[j] > x && j >= 0) { // uma op, # (inverteu a ordem)
                v[j + gap] = v[j]; // uma op
                j -= gap;
                op += 2; // #
            }
            if (j >= 0) // #
                op++; // #
            v[j + gap] = x; // uma op
            op++; // #
        }
        gap /= 2;
    }
    return op; // #
}

// quick do ads
// as alterações do arquivo q ele soltou vão estar marcadas com "#"
int quick(int v[], int f, int l) { // #
    int op = 0; // #
    if (f >= l) {
        return 0; // #
    }
    int m = (l + f)/2;
    int pivot = v[m]; // uma op
    int i = f;
    int j = l;
    op++; // #
    while(1) {
        while(v[i] < pivot) { // uma op
            i++;
            op++; // #
        }
        while(v[j] > pivot) { // uma op
            j--;
            op++; // #
        }
        op += 2; // #

        if (i >= j) {
            break;
        }
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
        i++;
        j--;
        op += 3; // #
    }
    op += quick(v, f, j); // #
    op += quick(v, j+1, l); // #
    return op; // #
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

        // print noq o ads quer
        if (quick(tempQ, 0, i) < shell(tempS, i+1))
            printf("Q");
        else if (quick(tempQ, 0, i) > shell(tempS, i+1))
            printf("S");
        else
            printf("-");

//        // bloco de texto pra ver se o quick tá ordenando
//        printf("quicj ordenado: ");
//        for (int j = 0; j < i+1; j++)
//            printf("%d ", tempQ[j]);
//        printf("\n");
//
//        // bloco de texto pra ver se o shell tá ordenando
//        printf("shell ordenado: ");
//        for (int j = 0; j < i+1; j++)
//            printf("%d ", tempS[j]);
//        printf("\n");
//
//        // bloco de comando pra ver se o quick tá contando certo
//        printf("quicj n_op: ");
//        printf("%d ", quick(tempQ, 0, i));
//        printf("\n");
//
//        // bloco de comando pra ver se o quick tá contando certo
//        printf("shell n_op: ");
//        printf("%d ", shell(tempS, i+1));
//        printf("\n");
//        printf("\n");

        // já da free de uma vez logo
        free(tempS);
        free(tempQ);
    }

    // free no vetor ai
    free(vet);

    return 0;
}