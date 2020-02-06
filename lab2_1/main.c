#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int range = 51;

void print_matrix(int8_t **A, int M, int N) {
    int i, j;
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%d\t", *(*(A + i) + j));
        }
        printf("\n");
    }
}
int is_in_row(int8_t* row, int8_t num, int N){
    int i;
    for (i = 0; i < N; ++i){
        if (*(row + i) == num){
            return 1;
        }
    }
    return 0;
}

int are_rows_similar(int8_t* row_1, int8_t* row_2, int N) {
    int i;
    for (i =0; i<N; ++i){
        if( !is_in_row(row_1, *(row_2 + i), N)){
            return 0;
        }
    }
    return 1;
}

int8_t ** generate_matrix(int M, int N){
    int i,j;
    int8_t ** A = (int8_t **) malloc(M* sizeof(int8_t *));
    for (i = 0; i < M; ++i){
        *(A+i) = (int8_t*) malloc(N * sizeof(int8_t));
    }
    for (i = 0; i < M; ++i) {
        // uncomment to group up rows (then no print)
//        int count = 0;
        for (j = 0; j < N; ++j) {
            *(*(A+i)+ j)= random() % range;
//            int8_t num = rand() % range;
//            if (!is_in_row(*(A+i), num, count)){
//                *(*(A+i)+ ++count)= num;
//            }
        }
    }
    return A;
}

int main() {
    clock_t start = clock();
    srandom(time(NULL));
    int N = 0, M = 0, count = 0;
    int i;
    printf("Программа находит количество строк в заданной матрице A размером M x N, которые похожи на первую (все элементы заданной строки есть в первой).\n");
    printf("Введите число M (> 0):");
    do {
        scanf("%d", &M);
    } while (M < 1);
    printf("Введите число N (> 0):");
    do {
        scanf("%d", &N);
    } while (N < 1);
    int8_t ** A = generate_matrix(M, N);
    printf("\n\n");

    print_matrix(A, M, N);
    printf("\n\n");

    for (i = 1; i < M; ++i){
        if (are_rows_similar(*A, *(A + i), N)){
            ++count;
        }
    }

    printf("Количество похожих строк: %d", count);
    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}
