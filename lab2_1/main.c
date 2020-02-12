#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int range = 11;

void print_matrix(int8_t **A, int M, int N) {
    int i, j;
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            printf("%d\t", *(*(A + i) + j));
        }
        printf("\n");
    }
}

void move_row(int8_t *row, int from, int N) {
    int i;
    for (i = N; i > from; --i) {
        *(row + i + 1) = *(row + i);
    }
}

int insert_in_row(int8_t *row, int8_t num, int N) {
    int i, index = 0;
    for (i = 0; i < N; ++i) {
        if (*(row + i) == num) {
            return 0;
        } else if (*(row + i) > num) {
            break;
        } else if (*(row + i) < num) {
            ++index;
        }
    }
    if (index < N) {
        move_row(row, index - 1, N);
        *(row + index) = num;
    } else if (N == 0) {
        *row = num;
    } else {
        *(row + N) = num;
    }
    return 1;
}

int count_in_sort_matrix(int8_t **A, int M, int N) {
    // Group matrix
    int8_t *size_array = (int8_t *) malloc(N * sizeof(int8_t));
    int i, j;
    int8_t **B = (int8_t **) malloc(M * sizeof(int8_t *));
    for (i = 0; i < M; ++i) {
        *(B + i) = (int8_t *) malloc(N * sizeof(int8_t));
    }

    for (i = 0; i < M; ++i) {
        int count = 0;
        for (j = 0; j < N; ++j) {
            if (insert_in_row(*(B + i), *(*(A + i) + j), count)) {
                ++count;
            }
        }
        *(size_array + i) = count;
    }


    for (i = 0; i < M; ++i) {
        for (j = 0; j < size_array[i]; ++j) {
            printf("%d\t", *(*(B + i) + j));
        }
        printf("\n");
    }
    int count_similar = 0;
    for (i = 1; i < M; ++i) {
        int flag = 1;
        if (size_array[0] == size_array[1]) {
            for (j = 0; j < size_array[0]; ++j) {
                if (B[0][j] != B[i][j]) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                count_similar++;
            }
        }
    }
    return count_similar;
}

int8_t **generate_matrix(int M, int N) {
    int i, j;
    int8_t **A = (int8_t **) malloc(M * sizeof(int8_t *));
    for (i = 0; i < M; ++i) {
        *(A + i) = (int8_t *) malloc(N * sizeof(int8_t));
    }
    for (i = 0; i < M; ++i) {
        for (j = 0; j < N; ++j) {
            *(*(A + i) + j) = random() % range;
        }
    }
    return A;
}

int main() {
    srandom(time(NULL));
    int N = 0, M = 0, count = 0;
    printf("Программа находит количество строк в заданной матрице A размером M x N, которые похожи на первую (все элементы заданной строки есть в первой).\n");
    printf("Введите число M (> 0):");
    do {
        scanf("%d", &M);
    } while (M < 1);
    printf("Введите число N (> 0):");
    do {
        scanf("%d", &N);
    } while (N < 1);
    int8_t **A = generate_matrix(M, N);
    printf("\n\n");

    print_matrix(A, M, N);
    printf("\n\n");

    clock_t start = clock();

    count = count_in_sort_matrix(A, M, N);
    printf("Количество похожих строк: %d", count);
    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
    return 0;
}
