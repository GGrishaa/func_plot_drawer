#include "stack.h"

struct Stack* op_init() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (stack == NULL) {
        return 0;
    }
    stack->top = NULL;
    return stack;
}

void op_push(struct Stack* stack, char op) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = op;
    newNode->next = stack->top;
    stack->top = newNode;
}

int op_pop(struct Stack* stack) {
    if (stack->top == NULL) {
        return 0;
    }
    struct Node* temp = stack->top;
    char op = temp->data;
    stack->top = temp->next;
    free(temp);
    return op;
}

int op_peek(struct Stack* stack) { return stack->top->data; }

void op_destroy(struct Stack* stack) {
    while (stack->top != NULL) {
        op_pop(stack);
    }
    free(stack);
}

struct NumStack* num_init() {
    struct NumStack* stack = (struct NumStack*)malloc(sizeof(struct NumStack));
    if (stack == NULL) {
        return 0;
    }
    stack->top = NULL;
    return stack;
}

void num_push(struct NumStack* stack, double value) {
    struct NumNode* newNode = (struct NumNode*)malloc(sizeof(struct NumNode));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->value = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

double num_pop(struct NumStack* stack) {
    if (stack->top == NULL) {
        return 0;
    }
    struct NumNode* temp = stack->top;
    double value = temp->value;
    stack->top = temp->next;
    free(temp);
    return value;
}

double num_peek(struct NumStack* stack) { return stack->top->value; }

void num_destroy(struct NumStack* stack) {
    while (stack->top != NULL) {
        num_pop(stack);
    }
    free(stack);
}
