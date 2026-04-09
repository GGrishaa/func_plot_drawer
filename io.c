#include "io.h"

int is_digit(char ch) { return (ch <= '9' && ch >= '0'); }

int is_letter(char ch) { return (ch >= 'a' && ch <= 'z'); }

int is_op(char ch) { return strchr("+-*/()", ch) != NULL; }

int is_func_or_x(const char *token) {
    const char *funcs_x[] = {"sin", "cos", "tan", "ctg", "sqrt", "ln", "x"};
    for (int i = 0; i < 7; ++i) {
        if (strcmp(token, funcs_x[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int number(const char *expr, int *pos, char *token) {
    int j = 0, correct = 1;
    while (is_digit(expr[*pos])) {
        token[j++] = expr[(*pos)++];
    }
    if (expr[*pos] == '.') {
        token[j++] = expr[(*pos)++];
        if (!is_digit(expr[*pos])) {
            correct = 0;
        }
        while (is_digit(expr[*pos]) && correct) {
            token[j++] = expr[(*pos)++];
        }
    }
    token[j] = '\0';
    return (correct && j > 0);
}

void func_or_x(const char *expr, int *pos, char *token) {
    int j = 0;
    while (is_letter(expr[*pos])) {
        token[j++] = expr[(*pos)++];
    }
    token[j] = '\0';
    if (j == 1 && token[0] == 'x') {
        return;
    }
    if (expr[*pos] != '(') {
        token[0] = '\0';
    }
}

int tokenize(const char *expr, char **tokens) {
    int count = 0, pos = 0, length = strlen(expr), correct = (length > 0);
    while (pos < length && count < MAX_TOKENS && correct) {
        if (is_digit(expr[pos])) {
            correct = number(expr, &pos, tokens[count]);
            if (correct) {
                ++count;
            } else {
                correct = 0;
            }
        } else if (is_letter(expr[pos])) {
            func_or_x(expr, &pos, tokens[count]);
            if (is_func_or_x(tokens[count])) {
                ++count;
            } else {
                correct = 0;
            }
        } else if (is_op(expr[pos])) {
            if (expr[pos] == '-' && (pos == 0 || expr[pos - 1] == '(')) {
                tokens[count][0] = '~';
                tokens[count][1] = '\0';
                ++pos;
            } else {
                tokens[count][0] = expr[pos++];
                tokens[count][1] = '\0';
            }
            ++count;
        } else {
            correct = 0;
        }
    }
    shorten(tokens);
    return (correct == 1) ? count : -1;
}

void shorten(char **tokens) {
    for (int i = 0; i < MAX_TOKENS && tokens[i][0] != '\0'; i++) {
        if (strcmp(tokens[i], "sin") == 0) {
            tokens[i][0] = 's';
            tokens[i][1] = '\0';
        } else if (strcmp(tokens[i], "cos") == 0) {
            tokens[i][0] = 'c';
            tokens[i][1] = '\0';
        } else if (strcmp(tokens[i], "tan") == 0) {
            tokens[i][0] = 't';
            tokens[i][1] = '\0';
        } else if (strcmp(tokens[i], "ctg") == 0) {
            tokens[i][0] = 'g';
            tokens[i][1] = '\0';
        } else if (strcmp(tokens[i], "sqrt") == 0) {
            tokens[i][0] = 'q';
            tokens[i][1] = '\0';
        } else if (strcmp(tokens[i], "ln") == 0) {
            tokens[i][0] = 'l';
            tokens[i][1] = '\0';
        }
    }
}

void to_opn(char **tokens, int token_count, char **output) {
    struct Stack *s = op_init();
    int index = 0;
    for (int i = 0; i < token_count; ++i) {
        char *token = tokens[i];
        if (is_number(token) || strcmp(token, "x") == 0) {
            strcpy(output[index++], token);
        } else if (strchr("sctgql", token[0]) != NULL) {
            op_push(s, token[0]);
        } else if (strcmp(token, "(") == 0) {
            op_push(s, '(');
        } else if (strcmp(token, ")") == 0) {
            while (s->top != NULL && op_peek(s) != '(') {
                output[index][0] = op_pop(s);
                output[index++][1] = '\0';
            }
            op_pop(s);
            if (s->top != NULL && strchr("sctgql", op_peek(s)) != NULL) {
                output[index][0] = op_pop(s);
                output[index++][1] = '\0';
            }
        } else if (strchr("+-*/~", token[0]) != NULL && token[1] == '\0') {
            char op = token[0];
            while (s->top != NULL && priority(op_peek(s)) >= priority(op)) {
                output[index][0] = op_pop(s);
                output[index++][1] = '\0';
            }
            op_push(s, op);
        }
    }
    while (s->top != NULL) {
        output[index][0] = op_pop(s);
        output[index++][1] = '\0';
    }
    op_destroy(s);
}

int priority(char ch) {
    int ans = 4;
    if (ch == ')' || ch == '(') {
        ans = 0;
    } else if (ch == '+' || ch == '-') {
        ans = 1;
    } else if (ch == '*' || ch == '/') {
        ans = 2;
    } else if (ch == '~') {
        ans = 3;
    }
    return ans;
}

void input(char *expr) {
    int n = 0;
    char ch = getchar();
    while (ch != '\n') {
        expr[n] = ch;
        ++n;
        ch = getchar();
    }
    expr[n] = '\0';
}

void substitute_x(char **tokens, int token_count, double x_value) {
    for (int i = 0; i < token_count; i++) {
        if (strcmp(tokens[i], "x") == 0) {
            snprintf(tokens[i], MAXLEXEM, "%.6f", x_value);
        }
    }
}

int is_number(char *token) {
    char *ch;
    strtod(token, &ch);
    return ch != token && *ch == '\0';
}

double function(char **tokens, int token_count) {
    struct NumStack *s = num_init();
    for (int i = 0; i < token_count; ++i) {
        char *token = tokens[i];
        if (is_number(token)) {
            num_push(s, atof(token));
        } else if (!strcmp(token, "~")) {
            if (s->top != NULL) {
                double val = num_pop(s);
                num_push(s, -val);
            }
        } else if (!strcmp(token, "s")) {
            num_push(s, sin(num_pop(s)));
        } else if (!strcmp(token, "c")) {
            num_push(s, cos(num_pop(s)));
        } else if (!strcmp(token, "t")) {
            num_push(s, tan(num_pop(s)));
        } else if (!strcmp(token, "g")) {
            num_push(s, 1.0 / tan(num_pop(s)));
        } else if (!strcmp(token, "q")) {
            num_push(s, sqrt(num_pop(s)));
        } else if (!strcmp(token, "l")) {
            num_push(s, log(num_pop(s)));
        } else if (!strcmp(token, "+")) {
            double b = num_pop(s);
            double a = num_pop(s);
            num_push(s, a + b);
        } else if (!strcmp(token, "-")) {
            double b = num_pop(s);
            double a = num_pop(s);
            num_push(s, a - b);
        } else if (!strcmp(token, "*")) {
            double b = num_pop(s);
            double a = num_pop(s);
            num_push(s, a * b);
        } else if (!strcmp(token, "/")) {
            double b = num_pop(s);
            double a = num_pop(s);
            num_push(s, a / b);
        }
    }
    double res = num_pop(s);
    num_destroy(s);
    return res;
}

void draw(struct point *points) {
    for (int y = 0; y < Y; ++y) {
        for (int x = 0; x < X; ++x) {
            printf("%c", is_point(points, y, x) ? '*' : '.');
        }
        printf("\n");
    }
}

void debug_opn(char **opn, int count) {
    printf("OPN: ");
    for (int i = 0; i < count && opn[i][0] != '\0'; i++) {
        printf("%s ", opn[i]);
    }
    printf("\n");
}
