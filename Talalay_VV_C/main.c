//
//  main.c
//  Talalay_VV_C
//
//  Created by Vitaliy Talalay on 18.12.2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define T char

void menu(void);

struct TNode {
    T value; // Данные
    struct TNode *next; //Указатель на следующий элемент списка
};
typedef struct TNode Node;
struct Node* Head=NULL;
struct TStack {
    Node *head;
    int size;
    int maxSize;
};
struct TStack Stack;

void task1(void);
void push(T c, struct TStack *stack);
T pop(struct TStack *stack);
int is_empty(struct TStack *stack);

void pushBrackets(char value);
char popBrackets(void);
void bracketsSequence(void);

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
                bracketsSequence();
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
    printf("'1' - Перевод числа из DEC в BIN\n");
    printf("'2' - Проверка скобочной последовательности\n");
    printf("'0' - Выход\n");
    printf("******************\n");
}

/*
 1. Реализовать перевод из десятичной в двоичную систему счисления с
 использованием стека.
 */

void task1() {
    int temp;
    int inputNumber;
    printf("Введите число для перевода в двоичную систему:\n");
    scanf("%d", &temp);
    inputNumber = temp;
    int n;
    while(temp >= 2) {
        n = (temp % 2);
        temp = temp / 2;
        push(n ? '1' : '0', &Stack);
    }
    push(temp ? '1' : '0', &Stack);
    struct TStack copy(struct TStack stack);
    printf("Число %i в двоичном формате: ", inputNumber);
    while (!is_empty(&Stack))
        printf("%c",pop(&Stack));
    printf("\n");
}

/*
 + 2. Добавить в программу «реализация стека на основе односвязного списка»
 проверку на выделение памяти. Если память не выделяется, то выводится
 соответствующее сообщение.
 */

void push(T c, struct TStack *stack) {
    Node *temp;
    temp = (Node*) malloc(sizeof(Node));
    // 2. Проверка на выделение памяти
    if (temp == NULL){
        printf("Память не была выделена/n");
        return;
    }
    temp->value = c;
    temp->next = stack->head;
    stack->head = temp;
    ++stack->size;
}

T pop(struct TStack *stack) {
    if (is_empty(stack))
        return '_';
    T c;
    Node *temp;
    temp = (Node*) malloc(sizeof(Node));
    c = stack->head->value;
    temp = stack->head;
    stack->head = temp->next;
    free(temp);
    --stack->size;
    return c;
}

int is_empty(struct TStack *stack) {
    return (stack->size == 0);
}

/*
 3. Написать программу, которая определяет, является ли введенная скобочная
 последовательность правильной. Примеры правильных скобочных выражений:
 (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(])
 для скобок [,(,{.
 Например: (2+(2*2)) или [2/{5*(4+7)}]
 (({{[]}}))
 ])})
 */

void pushBrackets(char value) {
    if (Stack.size >= Stack.maxSize) {
        printf("Стэк переполнен\n");
        return;
    }
    Node *tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("Память не была выделена\n");
        return;
    } else {
        tmp->value = value;
        tmp->next = Stack.head;
        Stack.head = tmp;
        Stack.size++;
    }
}

char popBrackets(void) {
    if (Stack.size == 0) return '!';
    Node* next = NULL;
    char value;
    value = Stack.head->value;
    next = Stack.head;
    Stack.head = Stack.head->next;
    free(next);
    Stack.size--;
    return value;
}

int isForwardBracket(char symbol) {
    if (symbol == '(' || symbol == '[' || symbol == '{') return 1;
    else return 0;
}

int isBackwardBracket(char symbol) {
    if (symbol == ')' || symbol == ']' || symbol == '}') return 1;
    else return 0;
}

int isNumber(char *str) {
    int i = 0;
    while (str[i] != '\0')
        if (!isdigit(str[i++])) return 0;
    return 1;
}

void bracketsSequence(void) {
    Stack.maxSize = 100;
    int backwardIsFirst = 0;
    char buffer[100];
    printf("Введите скобочную последовательность: ");
    scanf("%s", buffer);

    for (int i = 0; i < strlen(buffer); i++) {
        if (isForwardBracket(buffer[i])) {
            printf("Открывающая скобка %c в %i позиции\n", buffer[i], i+1);
            pushBrackets(buffer[i]);
        }

        if (isBackwardBracket(buffer[i])) {
            printf("Закрывающая скобка %c в %i позиции\n", buffer[i], i+1);
            char charFromStack = popBrackets();
            if (charFromStack == '!') {
                backwardIsFirst = 1;
                break;
            }
            if ((charFromStack == '(' && buffer[i] != ')') ||
                (charFromStack == '[' && buffer[i] != ']') ||
                (charFromStack == '{' && buffer[i] != '}')) {
                printf("Скобка %c в %i позиции неправильная\n", buffer[i], i+1);
                break;
            }
        }
    }

    char lastCharFromStack = popBrackets();

    if (lastCharFromStack != '!') printf("Не хватает закрывающих скобок\n");
    else {
        if (backwardIsFirst) printf("Неправильная последовательность скобок\n");
        else printf("Последовательность скобок правильная\n");
    }
}
