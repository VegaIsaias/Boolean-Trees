//
// Created by Isaias Perez Vega
//
// Library Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_CHARS 32000

// Stack Struct
struct stack {
    char data;
    struct stack *next;
};

// FUNCTION SIGNATURES //S
void init(struct stack **front);
int push(struct stack **front, char num);
struct stack* pop(struct stack **front);
int evaluateExp(char* exp, struct stack** myStruct);
int empty(struct stack *front);

int main(void) {
    int result;
    int exit = 0;
    char* exp = NULL;
    struct stack* myStack;
    int casenum = 1;

    do {

        init(&myStack);

        // Getting expression from input
        exp = malloc(sizeof(char) * MAX_CHARS + 1);
        scanf("%s", exp);

        if (strcmp(exp, "()") == 0) {
            exit = 1;
        }

        //EVALUATE EXP
        result = evaluateExp(exp, &myStack);

        if (result == 1) {
            printf("%d. True\n", casenum);
        } else if (result == 0){
            printf("%d. False\n", casenum);
        }

        casenum++;
        free(exp); exp = NULL;

    } while (!exit);
    return 0;
}


// EVALUATE AND/OR EXPRESSION //
int evaluateExp(char* exp, struct stack** front) {

    int result; char update = '\0';
    if (exp != NULL) {

        int level = 0; char* subExp = NULL; char boolean;
        subExp = malloc(sizeof(char) * strlen(exp));
        struct stack* tmp; int subIndex = 0;
        int x;

        // For every character in expression
        unsigned long expLen = strlen(exp);
        for (x = 0; x < expLen; x++) {

            // If '(' in string, push to stack
            if (strcmp(&exp[x], "(") == 0) {
                push(front, exp[x]);
                level++;

            // If ')' in string, pop until first '('
            } else if (strcmp(&exp[x], "F") == 0 || strcmp(&exp[x], "T") == 0) {

                push(front, exp[x]);

            } else if (strcmp(&exp[x], ")") == 0) {

                if (empty(*front)) break;
                //Get top of stack
                tmp = pop(front);
                boolean = tmp->data;
                free(tmp); tmp = NULL;
                char* letter;

                // Get subExpression
                while (boolean != '(') {
                    tmp = pop(front);
                    boolean = tmp->data;
                    free(tmp); tmp = NULL;
                    //strcpy(&subExp[subIndex++], &boolean);
                    subExp[subIndex++] = boolean;
                }

                // OR
                if (level % 2 == 0) {
                    letter = strstr(subExp, "T");
                    if (letter) {
                        update = 'T';
                        push(front, update);
                    } else {
                        update = 'F';
                        push(front, update);
                    }
                // AND
                } else if (level % 2 == 1) {
                    letter = strstr(subExp, "F");
                    if (letter) {
                        update = 'F';
                        push(front, update);
                    } else {
                        update = 'T';
                        push(front, update);
                    }
                }
                level--;
            }
        }
        if (update == 'T') {
            result = 1;
        } else {
            result = 0;
        }

    } else {
        printf("Couldn't evaluate, expression is null\n");
        exit(0);
    }

    return result;
}

// INITIATES THE FRONT OF THE STACK //
void init(struct stack **front) {
    *front = NULL;
}

// PUSH NUM ONTO STACK, RETURN POINTER TO FRONT //
int push(struct stack **front, char num) {

    struct stack *temp;
    // Create temp node and link it to front.
    temp = (struct stack *)malloc(sizeof(struct stack));

    if (temp != NULL) {
        temp->data = num;
        //printf("pushed: %c\n", temp->data);
        temp->next = *front;
        *front = temp;
        return 1;
    }
    else
        return 0;
}

// POP THE TOP OF THE STACK, RETURN POINTER TO FRONT OF THE STACK //
struct stack* pop(struct stack **front) {

    struct stack *temp;
    temp = NULL;

    if (*front != NULL) {
        temp = (*front);
        *front = (*front)->next;
        temp -> next = NULL;
    }
    //printf("popped: %c\n", temp->data);
    return temp;
}

// RETURN TRUE IF STACL IS CURRENTLY EMPTY //
int empty(struct stack *front) {
    if (front == NULL)
        return 1;
    else
        return 0;
}
