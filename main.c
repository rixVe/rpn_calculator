#include "stack.h"
#include "vector.h"
#include "hashmap.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char operations[] = {
    '-',
    '+',
    '*',
    '/',
    '%',
    '^',
};
int weights[] = {
    0,
    0,
    1,
    1,
    1,
    2
};

int main(int argc, char **argv) {
    // TODO files
    Map operations_map;
    map_initialize(&operations_map, sizeof(char), sizeof(int));
    for (int i = 0; i < 6; i++) {
        map_set(&operations_map, &operations[i], &weights[i]);
    }
    Vector equation;
    vector_initialize(&equation, sizeof(char *));
    for (int i = 1; i < argc; ++i) {
        vector_push(&equation, &argv[i]);
    }

    Vector ans;
    vector_initialize(&ans, sizeof(char *));

    Stack operator_stack;
    stack_initialize(&operator_stack, sizeof(char *));

    char *token;
    char *buffer;
    for (int i = 0; i < vector_get_size(&equation); ++i) {
        vector_get(&equation, i, &token);
        if (isdigit(*token)) {
            vector_push(&ans, &token);
        } else if (strcmp(token, ",") == 0) {
            char *op;
            while (!stack_is_empty(&operator_stack)) {
                stack_peep(&operator_stack, &op);
                if (strcmp(op, "(") == 0) {
                    break;
                }
                stack_pop(&operator_stack, &op);
                vector_push(&ans, &op);
            }
        } else if (strcmp(token, "(") == 0) {
            stack_push(&operator_stack, &token);
        } else if (strcmp(token, ")") == 0) {
            if (stack_is_empty(&operator_stack)) return -1;
            char *op;
            bool found = false;
            while (!stack_is_empty(&operator_stack)) {
                stack_pop(&operator_stack, &op);
                if (strcmp(op, "(") == 0) {
                    found = true;
                    break;
                }

                vector_push(&ans, &op);
            }
            if (!found) return -1;
            stack_peep(&operator_stack, &buffer);
            if (!map_contains_key(&operations_map, buffer) && !isdigit(*buffer) && !(strcmp(buffer, ",") == 0) && !(
                    strcmp(token, "(") == 0) && !(strcmp(token, ")") == 0)) {
                stack_pop(&operator_stack, &buffer);
                vector_push(&ans, &buffer);
            }
        } else if (map_contains_key(&operations_map, token)) {
            char *pop_buff;
            while (!stack_is_empty(&operator_stack)) {
                stack_peep(&operator_stack, &buffer);
                if (strcmp(buffer, "(") == 0) {
                    break;
                }
                if (!map_contains_key(&operations_map, buffer)) {
                    stack_pop(&operator_stack, &pop_buff);
                    vector_push(&ans, &pop_buff);
                    continue;
                }
                if (*(int *) map_get_value(&operations_map, buffer) >= *(int *) map_get_value(&operations_map, token)) {
                    stack_pop(&operator_stack, &pop_buff);
                    vector_push(&ans, &pop_buff);
                } else {
                    break;
                }
            }

            stack_push(&operator_stack, &token);
        } else {
            //custom function
            stack_push(&operator_stack, &token);
        }
    }
    while (!stack_is_empty(&operator_stack)) {
        stack_pop(&operator_stack, &buffer);
        if (strcmp(buffer, "(") == 0) {
            return -1;
        }
        vector_push(&ans, &buffer);
    }


    char *buff;
    for (int i = 0; i < vector_get_size(&ans); ++i) {
        vector_get(&ans, i, &buff);
        printf("%s ", buff);
    }

    vector_free(&equation);
    vector_free(&ans);
    stack_free(&operator_stack);
    map_free(&operations_map);
    return 0;
}
