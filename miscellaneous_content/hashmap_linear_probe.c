#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define CMD_QUERY   'q'
#define CMD_INSERT  'i'
#define CMD_PRINT   'p'
#define SIZE        10
#define EMPTY       -1

int hash(uint32_t epic);
void hash_insert(int64_t *hash_table, uint32_t data);
void hash_query(int64_t *hash_table, uint32_t data);
void print_table(int64_t *hash_table);

int main(void) {
    char cmd;
    uint32_t data;
    int64_t hash_table[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        hash_table[i] = EMPTY;
    }

    while (scanf(" %c", &cmd) == 1) {
        if (cmd == CMD_INSERT) {
            scanf(" %d", &data);
            hash_insert(hash_table, data);
        } else if (cmd == CMD_QUERY) {
            scanf(" %d", &data);
            hash_query(hash_table, data);
        } else if (cmd == CMD_PRINT) {
            print_table(hash_table);
        } else {
            printf("Invalid command.");
        }
    }
    
    return 0;
}

int hash(uint32_t epic) {
    return epic % SIZE;
}

void hash_insert(int64_t *hash_table, uint32_t data) {
    int ideal_index = hash(data);
    bool inserted = false;

    int curr_index = ideal_index;
    while (!inserted) {
        if (hash_table[curr_index] == EMPTY) {
            hash_table[curr_index] = data;
            inserted = true;
            printf("Inserted %u at index %d\n", data, curr_index);
            return;
        }

        curr_index++;
        if (curr_index == SIZE) {
            curr_index = 1;
        }
        if (curr_index == ideal_index) {
            printf("The table's full.\n");
            return;
        }
    }
}

void hash_query(int64_t *hash_table, uint32_t data) {
    int ideal_index = hash(data);
    bool inserted = false;

    int curr_index = ideal_index;
    while (!inserted) {
        if (hash_table[curr_index] == data) {
            printf("Found %u at index %d.\n", data, curr_index);
            return;
        }

        curr_index++;
        if (curr_index == SIZE) {
            curr_index = 1;
        }
        if (curr_index == ideal_index || hash_table[curr_index] == EMPTY) {
            printf("%d does not exist in the table.\n", data);
            return;
        }
    }
}

void print_table(int64_t *hash_table) {
    for (int i = 0; i < SIZE; ++i) {
        printf("| %ld | ", hash_table[i]);
    }
    printf("\n");
}