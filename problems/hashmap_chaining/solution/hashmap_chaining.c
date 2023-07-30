#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_handler(unordered_map hashmap, int key_hv, struct Value *insert);

// Your TODOS
int string_to_int(char *str) {
  int res = 0;
  for (int i = 0; i < strlen(str); ++i) {
    res += str[i];
  }
  return res;
};

// Really basic modulo hashing function:
// Takes in a string called str, and m should be a prime
// number representing bucket_count
int hash(char *str, int m) { return string_to_int(str) % m; }

unordered_map HashMap_new(int n) {
  unordered_map new = malloc(sizeof(struct HashMap));

  int pn = next_prime(n);

  new->bucket_count = pn;
  new->buckets = malloc(pn * sizeof(struct Value));

  // Initialise our malloced array
  for (int i = 0; i < pn; ++i) {
    new->buckets[i] = NULL;
  }

  return new;
};

void HashMap_insert(unordered_map hashmap, char *key, char *value) {
  struct Value *new = malloc(sizeof(struct Value));
  new->key = key;
  new->value = value;
  new->next = NULL;

  int key_hv = hash(key, hashmap->bucket_count);

  insert_handler(hashmap, key_hv, new);
};

void insert_handler(unordered_map hashmap, int key_hv, struct Value *insert) {

  if (hashmap->buckets[key_hv] == NULL) {
    hashmap->buckets[key_hv] = insert;
    return;
  }
  struct Value *curr = hashmap->buckets[key_hv];

  if (strcmp(curr->key, insert->key) == 0) {
    curr->value = insert->value;
    free(insert);
    return;
  }

  while (curr->next != NULL) {
    if (strcmp(curr->next->key, insert->key) == 0) {
      curr->next->value = insert->value;
      free(insert);
      return;
    }
    curr = curr->next;
  }
  curr->next = insert;
}

char *HashMap_get(unordered_map hashmap, char *key) {
  int key_hv = hash(key, hashmap->bucket_count);
  struct Value *curr = hashmap->buckets[key_hv];
  while (curr != NULL && strcmp(curr->key, key) != 0) {
    curr = curr->next;
  }
  return (curr == NULL) ? "Not Found" : curr->value;
};

/**
 * Given Functions, (Try not to change these)
 */

bool is_prime(int n) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (int i = 5; i * i < n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

int next_prime(int n) {
  if (n <= 2)
    return 2;

  while (!is_prime(n)) {
    n++;
  }
  return n;
}

void HashMap_print(unordered_map hashmap) {
  for (int i = 0; i < hashmap->bucket_count; ++i) {
    struct Value *curr = hashmap->buckets[i];
    int f = 0;
    printf("%d: ", i);
    while (curr != NULL) {
      if (f != 0) {
        printf("->%s %s", curr->key, curr->value);
      } else {
        printf("%s %s", curr->key, curr->value);
      }
      curr = curr->next;
      f++;
    }
    printf("\n");
  }
}

void HashMap_free(unordered_map hashmap) {
  for (int i = 0; i < hashmap->bucket_count; ++i) {
    struct Value *curr = hashmap->buckets[i];
    if (curr == NULL) {
      free(hashmap->buckets[i]);
      continue;
    }
    while (curr != NULL) {
      struct Value *temp = curr->next;
      free(curr->value);
      free(curr->key);
      free(curr);
      curr = temp;
    }
  }
  free(hashmap->buckets);
  free(hashmap);
}
