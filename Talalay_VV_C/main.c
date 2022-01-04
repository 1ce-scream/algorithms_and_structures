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

#define SIZE 20

void menu(void);

void task1(void);
unsigned long hash(char *lineText);

void task2(void);
typedef struct Node Node;
Node* getFreeNode(int value, Node *parent);
void insertNode(Node **head, int value);
void printTreeBrackets(Node *root);
void preOrderTravers(Node* root);
void inOrderTravers(Node* root);
void postOrderTravers(Node* root);
Node* searchNodeOnTree(Node* root, int nodeKey);

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
                task2();
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
    printf("'1' - Хэш функция\n");
    printf("'2' - Двоичное дерево поиска\n");
    printf("'0' - Выход\n");
    printf("******************\n");
}

/*
 Задание 1. Реализовать простейшую хеш-функцию.
 На вход функции подается строка, на выходе сумма кодов символов.
 */

void task1(void) {
    char inputText[100];
    printf("Простая хэш-функция\n");
    printf("Введите строку для генерации хэша: ");
    scanf("%s", inputText);
    unsigned long hashValue = hash(inputText);
    printf("Хэш: %lu\n", hashValue);
}

unsigned long hash(char *lineText) {
    int i = 0;
    unsigned long hashValue = 0;
    
    while(lineText[i] != '\0'){
        hashValue += lineText[i];
        i++;
    }
    return hashValue;
}

/*
 Задание 2. Переписать программу, реализующую двоичное дерево поиска.
 а) Добавить в него обход дерева различными способами;
 б) Реализовать поиск в двоичном дереве поиска;
 */

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

void task2(void)
{
    Node *Tree = NULL;
    int elements[SIZE] = {54, 20, 72, 34 ,9, 89, 74, 8, 27, 36, 70, 3, 80, 69, 73, 83, 71, 45, 56, 66};
    int searchedElement;
    
    for (int j = 0; j < SIZE; j++) {
        insertNode(&Tree, elements[j]);
    }
    
    printf("\nДвоичное дерево:\n");
    printTreeBrackets(Tree);
    
    printf("\nПрямой обход:\n");
    preOrderTravers(Tree);
    
    printf("\nСимметричный обход:\n");
    inOrderTravers(Tree);
    
    printf("\nОбратный обход:\n");
    postOrderTravers(Tree);
    
    printf("\nВведите элемент для поиска в дереве: ");
    scanf("%d", &searchedElement);
    printf("\nПуть к искомому элементу (%i) через дерево:\n", searchedElement);
    searchNodeOnTree(Tree, searchedElement);
}

Node* getFreeNode(int value, Node *parent) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void insertNode(Node **head, int value) {
    Node *tmp = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }
    
    tmp = *head;
    while (tmp) {
        if (value > tmp->data) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        } else if (value < tmp->data) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        } else {
            exit(2);
        }
    }
}

void printTreeBrackets(Node *root) {
    if (root) {
        printf("%d", root->data);
        if (root->left || root->right) {
            printf("(");
            
            if (root->left)
                printTreeBrackets(root->left);
            else
                printf("NULL");
            printf(",");
            
            if (root->right)
                printTreeBrackets(root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

void preOrderTravers(Node* root) {
    if (root) {
        printf("%i ", root->data);
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

void inOrderTravers(Node* root) {
    if (root) {
        inOrderTravers(root->left);
        printf("%i ", root->data);
        inOrderTravers(root->right);
    }
}

void postOrderTravers(Node* root) {
    if (root) {
        postOrderTravers(root->left);
        postOrderTravers(root->right);
        printf("%i ", root->data);
    }
}

Node* searchNodeOnTree(Node* root, int nodeKey) {
    if (root == NULL || nodeKey == root->data) {
        printf("%i\n", root->data);
        return root;
    }
    if (nodeKey < root->data) {
        printf("%i -> налево -> ", root->data);
        return searchNodeOnTree(root->left, nodeKey);
    } else {
        printf("%i -> направо -> ", root->data);
        return searchNodeOnTree(root->right, nodeKey);
    }
}
