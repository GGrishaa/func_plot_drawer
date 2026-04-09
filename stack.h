#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
};

struct NumNode {
    double value;
    struct NumNode* next;
};

struct NumStack {
    struct NumNode* top;
};

struct Stack* op_init();
void op_push(struct Stack* stack, char op);
int op_pop(struct Stack* stack);
int op_peek(struct Stack* stack);
void op_destroy(struct Stack* stack);

struct NumStack* num_init();
void num_push(struct NumStack* stack, double value);
double num_pop(struct NumStack* stack);
double num_peek(struct NumStack* stack);
void num_destroy(struct NumStack* stack);

#endif