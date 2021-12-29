//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//

#include <stdio.h>
#include <string.h>

#define SIZE 20
#define M 8
#define N 8

void menu(void);
void task1(void);
void print1(int n, int m, int a[N][M]);

void lcs(void);
void print2(unsigned long i, unsigned long j);
int c[SIZE][SIZE];
char x[SIZE], y[SIZE], b[SIZE][SIZE];

void task3(void);
void prepare_board(void);
void first_step(void);
int next_step(int m, int n, int count);
void print3(void);

int board[M][N];
int moves[8][2]  = {
    {-1, -2}, {-2, -1}, {-2,  1}, { 1, -2},
    {-1,  2}, { 2, -1}, { 1,  2}, { 2,  1}
};

int main(int argc, const char * argv[]) {
    int taskNumber = 0;
    do {
        menu();
        scanf("%i",&taskNumber);
        switch (taskNumber) {
            case 1:
                task1();
                break;
            case 2:
                lcs();
                break;
            case 3:
                task3();
                break;
            case 0:
                printf("Программа завершена, всего доброго!\n");
                break;
            default:
                printf("Такого задания нет\n");
                break;
        }
    }
    while (taskNumber != 0);
    return 0;
}

void menu() {
    printf("******************\n");
    printf("Введите номер задания:\n");
    printf("'1' - Маршруты с препятствиями\n");
    printf("'2' - Общая подпоследовательность\n");
    printf("'3' - Обход конем шахматной доски\n");
    printf("'0' - Выход\n");
    printf("******************\n");
}

/*
 1. *Количество маршрутов с препятствиями. Реализовать чтение массива с
 препятствием и нахождение количество маршрутов.
 */

void task1(void) {
    printf("Задание 1\n");
    int arr[M][N] = {{1,1,1,1,0,1,1,0},{0,1,0,1,1,1,1,1},{0,1,0,1,1,1,0,1},{1,1,1,1,1,1,1,1},{1,0,1,1,1,1,1,1},{1,0,1,1,1,1,0,1},{1,1,1,1,0,1,1,1},{1,1,1,1,1,1,0,1}};
    printf("Карта препятствий:\n");
    print1(N, M, arr);
    
    for(int i = 1; i < N; ++i)
        arr[i][0] *= arr[i-1][0];
    for(int j = 1; j < N; ++j)
        arr[0][j] *= arr[0][j-1];
    for (int i = 1; i < N; ++i)
        for (int j = 1; j < M; ++j)
            arr[i][j] *= (arr[i][j - 1] + arr[i - 1][j]);
    
    printf("Карта количества маршрутов:\n");
    print1(N, M, arr);
    printf("Максимальное колличество возможных маршрутов: %d\n", arr[M-1][N-1]);
}

void print1(int n, int m, int a[N][M]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("%6d", a[i][j]);
        }
        printf("\n");
    }
}

/*
 2. Решить задачу о нахождении длины максимальной последовательности с
 помощью матрицы.
 */

void lcs(void) {
    printf("Задание 2\n");
    int i, j;
    unsigned long m, n;
    
    printf("Введите первую последовательность: ");
    scanf("%s", x);
    printf("Введите вторую последовательность: ");
    scanf("%s", y);
    printf("\nНаибольшая общая подпоследовательность: ");
    
    m = strlen(x);
    n = strlen(y);
    for (i = 0; i <= m; ++i)
        c[i][0] = 0;
    for (i = 0; i <= n; ++i)
        c[0][i] = 0;
    
    
    for (i = 1; i <= m; ++i)
        for (j = 1; j <= n; ++j) {
            if (x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 'c';
            }
            else if (c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 'u';
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 'l';
            }
        }
    print2(m, n);
}

void print2(unsigned long i, unsigned long j) {
    if (i == 0 || j == 0)
        return;
    if (b[i][j] == 'c') {
        print2(i - 1, j - 1);
        printf("%c", x[i - 1]);
    }
    else if (b[i][j] == 'u')
        print2(i - 1, j);
    else
        print2(i, j - 1);
}

/*
 3. ***Требуется обойти конем шахматную доску размером NxM, пройдя через все
 поля доски по одному разу. Здесь алгоритм решения такой же, как в задаче о
 8 ферзях. Разница только в проверке положения коня.
 */

void task3(void) {
    printf("Задание 3\n");
    prepare_board();
    first_step();
    print3();
}

void prepare_board(void) {
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j)
            board[i][j] = 0;
}

void first_step(void) {
    for(int i = 0; i < M; ++i)
        for(int j = 0; j < N; ++j) {
            board[i][j] = 1;
            if (next_step(i, j, 1))
                return;
            board[i][j] = 0;
        }
}

int next_step(int m, int n, int count) {
    if (count == 64)
        return 1;
    for(int i = 0; i < 8; ++i) {
        int a = m + moves[i][0];
        int b = n + moves[i][1];
        if (!((a >= 0) && (a < M) && (b >= 0) && (b < N)))
            continue;
        if (board[a][b] != 0)
            continue;
        board[a][b] = count+1;
        if(next_step(a, b, count+1))
            return 1;
        board[a][b] = 0;
    }
    return 0;
}

void print3(void) {
    printf("Карта ходов коня:\n");
    for(int i = 0; i < M; ++i) {
        for(int j = 0; j < N; ++j) {
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }
}
