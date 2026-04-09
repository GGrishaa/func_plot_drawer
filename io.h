#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "point.h"
#include "stack.h"

#define MAX_TOKENS 100
#define MAXLEXEM 256
#define MAX_TOKEN_LEN 20

int is_digit(char ch);
int is_letter(char ch);
int is_op(char ch);
int is_func_or_x(const char* token);
int number(const char* expr, int* pos, char* token);
void func_or_x(const char* expr, int* pos, char* token);
int tokenize(const char* expr, char** tokens);
void shorten(char** tokens);
int check_br(const char* expr);

void to_opn(char** tokens, int token_count, char** output);
int priority(char ch);

void input(char* expr);
void substitute_x(char** tokens, int token_count, double x_value);
int is_number(char* token);
double function(char** tokens, int token_count);
void draw(struct point* points);
void debug_opn(char **opn, int count);

#endif
