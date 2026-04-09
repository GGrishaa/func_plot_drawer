#include "io.h"
#include "point.h"

int main() {
    char* expr = (char*)calloc(MAXLEXEM, sizeof(char));
    input(expr);
    char** tokens = (char**)calloc(MAX_TOKENS, sizeof(char*));
    char** opn = (char**)calloc(MAX_TOKENS, sizeof(char*));
    for (int i = 0; i < MAX_TOKENS; ++i) {
        tokens[i] = (char*)calloc(MAX_TOKEN_LEN, sizeof(char));
        opn[i] = (char*)calloc(MAX_TOKEN_LEN, sizeof(char));
    }
    int tokens_count = tokenize(expr, tokens);
    if (tokens_count > 0) {
        to_opn(tokens, tokens_count, opn);
        int opn_count = 0;
        while (opn_count < MAX_TOKENS && opn[opn_count][0] != '\0') {
            opn_count++;
        }
        debug_opn(opn, opn_count);
        struct point points[X];
        for (int i = 0; i < X; ++i) {
            char** opn_in_x = (char**)calloc(MAX_TOKENS, sizeof(char*));
            for (int j = 0; j < opn_count; ++j) {
                opn_in_x[j] = (char*)calloc(MAX_TOKEN_LEN, sizeof(char));
                strcpy(opn_in_x[j], opn[j]);
            }
            points[i].x = i;
            substitute_x(opn_in_x, opn_count, scaled_x(i));
            points[i].y = scaled_y(function(opn_in_x, opn_count));
            for (int j = 0; j < opn_count; ++j) {
                free(opn_in_x[j]);
            }
            free(opn_in_x);
        }
        draw(points);
    } else {
        printf("n/a");
    }
    for (int i = 0; i < MAX_TOKENS; ++i) {
        free(tokens[i]);
        free(opn[i]);
    }
    free(tokens);
    free(opn);
    free(expr);
    return 0;
}
