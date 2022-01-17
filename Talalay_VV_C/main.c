//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_SIZE 100
#define whiteNode 1
#define grayNode 2
#define blackNode 3

int matrix[MAX_SIZE][MAX_SIZE];
int countNodes = 0;
int stateMatrix[MAX_SIZE];
const char* fileName = "/Users/vitaliy/Education/Xcode/Quarter 1/C/Talalay_VV_C/Talalay_VV_C/Matrix.txt";

void menu(void);
void task1(void);
void task2(void);
void task3(void);

int main(int argc, const char * argv[]) {
    setlocale(LC_ALL, "RU");
    int taskNumber = 0;
    do {
        menu();
        scanf("%i",&taskNumber);
        switch (taskNumber) {
            case 1:
                task1();
                break;
            case 2:
                task2();
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

// 2. Написать рекурсивную функцию обхода графа в глубину.

void depthGraphTravers(int adjacencyMatrixArray[MAX_SIZE][MAX_SIZE],
                         int countNodes,
                         int currentNode) {
    for (int j = 0; j < countNodes; j++) {
        if (currentNode != 0 && stateMatrix[currentNode] == blackNode) {
            currentNode -= 1;
            printf("Возвращаемся к ноде %c(%i)\n", 65 + currentNode, currentNode);
        }
        
        if (currentNode < countNodes - 1) {
            if (adjacencyMatrixArray[currentNode][j] != 0 && stateMatrix[j] == whiteNode) {
                stateMatrix[j] = grayNode;
                printf("%c(%i) -> %c(%i)\n", 65 + currentNode, currentNode, 65 + j, j);
                stateMatrix[currentNode] = blackNode;
                currentNode = j;
                depthGraphTravers(adjacencyMatrixArray, countNodes, currentNode);
            }
        } else {
            printf("Самая далекая нода: %c(%i)\n", 65 + currentNode, currentNode);
        }
    }
    
    stateMatrix[currentNode] = blackNode;
}

void task2(void) {
    int initialNode = 0;
    readMatrix(fileName, matrix);
    printMatrix(matrix, countNodes);
    printf("\n");
    
    if (countNodes != 0) {
        for (int i = 0; i < countNodes; i++) {
            stateMatrix[i] = whiteNode;
        }
        stateMatrix[initialNode] = grayNode;
    } else {
        printf("Матрица пуста\n");
        exit(1);
    }
    
    depthGraphTravers(matrix, countNodes, initialNode);
}

// 3. Написать функцию обхода графа в ширину.

typedef struct Queue Queue;
typedef struct VertexGraph VertexGraph;

struct VertexGraph {
    struct VertexGraph* nextVertexNode;
    struct VertexGraph* previousVertexNode;
    int value;
};

struct Queue {
    VertexGraph* head;
    VertexGraph* tail;
    int size;
};

Queue queue_3;

void enQueue(Queue* queue, int value) {
    VertexGraph* tmp = (VertexGraph*)malloc(sizeof(VertexGraph));
    
    if (tmp == NULL) {
        printf("Память не была выделена\n");
    } else {
        tmp->nextVertexNode = queue->head;
        tmp->previousVertexNode = NULL;
        tmp->value = value;
        if (queue->head == NULL) {
            queue->tail = tmp;
        } else {
            queue->head->previousVertexNode = tmp;
        }
        queue->head = tmp;
        queue->size++;
    }
}

int deQueue(Queue* queue) {
    if (queue->size == 0) {
        printf("Очередь пуста\n");
        return -1;
    }
    
    int value = queue->tail->value;
    VertexGraph* tmp = queue->tail;
    queue->tail = queue->tail->previousVertexNode;
    
    if (queue->size > 1) queue->tail->nextVertexNode = NULL;
    else queue->head = NULL;
    
    queue->size--;
    free(tmp);
    
    return value;
}

void widthGraphTravers(int matrix[MAX_SIZE][MAX_SIZE], int countNodes) {
    if (countNodes != 0) {
        for (int i = 0; i < countNodes; i++) {
            stateMatrix[i] = whiteNode;
        }
    } else {
        printf("Граф пуст\n");
        exit(1);
    }
    
    stateMatrix[0] = grayNode;
    enQueue(&queue_3, 0);
    
    while (queue_3.size > 0) {
        int currentNode = deQueue(&queue_3);
        
        if (stateMatrix[currentNode] == grayNode) {
            for (int j = 0; j < countNodes; j++) {
                if (matrix[currentNode][j] != 0 && stateMatrix[j] == whiteNode) {
                    enQueue(&queue_3, j);
                    stateMatrix[j] = grayNode;
                    printf("%c(%i) -> %c(%i)\n", 65 + currentNode, currentNode, 65 + j, j);
                }
            }
            stateMatrix[currentNode] = blackNode;
        }
    }
}


void task3(void) {
    readMatrix(fileName, matrix);
    printMatrix(matrix, countNodes);
    printf("\n");
    widthGraphTravers(matrix, countNodes);
}
