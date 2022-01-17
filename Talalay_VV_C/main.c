//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//

#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100

const char* fileName = "Matrix.txt";


void menu(void);
void task1(void);

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
                //                task2();
                break;
            case 3:
                //                task3();
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
    printf("'1' - Чтение матрицы смежности из файла\n");
    printf("'2' - Обход графа в глубину\n");
    printf("'3' - Обход графа в ширину\n");
    printf("'0' - Выход\n");
    printf("******************\n");
}

/*
 1. Написать функцию, которая считывают матрицу смежности из файла и
 выводят ее на экран.
 */

int matrix[MAX_SIZE][MAX_SIZE];
int countNodes = 0;

void readMatrix(const char *fileName, int array[MAX_SIZE][MAX_SIZE]) {
    FILE *file;
    file = fopen(fileName,"r");
    if (file == NULL) {
        printf("Файл не найден\n");
        exit(1);
    }
    
    fscanf(file, "%i", &countNodes);
    if (countNodes > MAX_SIZE) {
        printf("Слишком большая матрица, необходимо изменить параметр `MAX_SIZE`\n");
        exit(1);
    }
    
    for (int i = 0; i < countNodes; i++) {
        for (int j = 0; j < countNodes; j++) {
            fscanf(file, "%i", &array[i][j]);
        }
    }
    fclose(file);
}

void printMatrix(int matrix[MAX_SIZE][MAX_SIZE], int numberOfVertices) {
    printf("%s", "        ");
    for (int i = 0; i < numberOfVertices; i++) {
        printf("%c(%i) ", 65 + i, i);
    }
    
    printf("\n");
    for (int i = 0; i < numberOfVertices; i++) {
        printf("%c(%i) ", 65 + i, i);
        for (int j = 0; j < numberOfVertices; j++) {
            printf("%5i", (matrix[i][j] == INFINITY) ? 0 : matrix[i][j]);
        }
        printf("\n");
    }
}

void task1(void) {
    printf("Матрица будет прочитана из файла: %s\n", fileName);
    readMatrix(fileName, matrix);
    printMatrix(matrix, countNodes);
}
