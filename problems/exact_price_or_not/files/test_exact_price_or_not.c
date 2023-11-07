#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "exact_price_or_not.h"

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'sumCoins' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER price
 *  2. INTEGER_ARRAY coins
 */

int main()
{
    int p = parse_int(ltrim(rtrim(readline())));

    int n = parse_int(ltrim(rtrim(readline())));

    int* coins_array = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {

        char *data = readline();
        int coins_array_item = parse_int(ltrim(rtrim(data)));
        *(coins_array + i) = coins_array_item;
        free(data);
    }

    int result = sumCoins(p, n, coins_array);

    printf("%d\n", result);

    free(coins_array);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    if (data == NULL) {
        return NULL; // Handle memory allocation failure
    }

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(line);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        char* new_data = realloc(data, alloc_length);

        if (!new_data) {
            free(data);
            return NULL; // Handle memory allocation failure
        }

        data = new_data;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        char* new_data = realloc(data, data_length);

        if (!new_data) {
            free(data);
            return NULL; // Handle memory allocation failure
        }

        data = new_data;
    } else {
        char* new_data = realloc(data, data_length + 1);

        if (!new_data) {
            free(data);
            return NULL; // Handle memory allocation failure
        }

        data = new_data;
        data[data_length] = '\0';
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return "\0";
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return "\0";
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}