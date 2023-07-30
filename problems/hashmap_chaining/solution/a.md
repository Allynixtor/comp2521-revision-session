# Answers


## Q1
Q1 has you implement a function that adds up each individual character of a string.

This should be relatively simple code:
```c
int string_to_int(char *str) {
  int res = 0;
  for (int i = 0; i < strlen(str); ++i) {
    res += str[i];
  }
  return res;
};
```
We iterate through the array, implicitly typecast `str[i]` into an integer and add it to our result.

## Q2
Q2 requires you to implement `HashMap_new.c` and `hash`.

Your hash function can have any signature but typically it will either be
```c
int hash(char *a, int m);

// or

int hash(int a, int m);
```
Your hash function should take in a string then convert it into an integer and hash it by m, or take in the integer of an already hashed string and hash it by m.

`HashMap_new.c` on the other hand requires you to create a new `struct HashMap` and return it.

```c
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
```
Because the number of buckets should be a prime number, we find the next prime after the size we are given, and set that as our `bucket_count` 
and allocate that number of buckets to our `new`. We then initialise all our buckets to `NULL`, and return it.

## Q3
The final task involves implementing `HashMap_insert` and `HashMap_get`.

`HashMap_insert` is a bit more complex as we need to implement chaining, as well as overwriting into it.

```c
void HashMap_insert(unordered_map hashmap, char *key, char *value) {
  struct Value *new = malloc(sizeof(struct Value));
  new->key = key;
  new->value = value;
  new->next = NULL;

  int key_hv = hash(key, hashmap->bucket_count);

  insert_handler(hashmap, key_hv, new);
};
```
First lets look at `HashMap_insert`. We initially allocate and iniitialise a `struct Value` as this is what our bucket holds pointers to.
Next, we find the hash value of our key, and then finally we call a helper function that handles the actual insertion into the hashmap.
```c
void insert_handler(unordered_map hashmap, int key_hv, struct Value *insert) {

  if (hashmap->buckets[key_hv] == NULL) {
    hashmap->buckets[key_hv] = insert;
    return;
  }
  struct Value *curr = hashmap->buckets[key_hv];

  if (strcmp(curr->key, insert->key) == 0) {
    free(curr->value);
    curr->value = insert->value;
    free(insert->key);
    free(insert);
    return;
  }

  while (curr->next != NULL) {
    if (strcmp(curr->next->key, insert->key) == 0) {
      free(curr->next->value);
      curr->next->value = insert->value;
      free(insert->key);
      free(insert);
      return;
    }
    curr = curr->next;
  }
  curr->next = insert;
}
```
Our `insert_handler` may seem a bit longer, but it may also look somewhat familiar to you, this is because we are simply just inserting onto
the end of a linked list. Here we handle the two initial cases where our bucket is currently empty, or if the first element in our bucket has the same key.

Otherwise, we traverse until the end of the linked list, or until we find a similar key, and then we respectively insert onto the end, or replace the value at that key.

Our `HashMap_Get` is also quite similar to how we would traverse a linked list.
```c
char *HashMap_get(unordered_map hashmap, char *key) {
  int key_hv = hash(key, hashmap->bucket_count);
  struct Value *curr = hashmap->buckets[key_hv];
  while (curr != NULL && strcmp(curr->key, key) != 0) {
    curr = curr->next;
  }
  return (curr == NULL) ? "Not Found" : curr->value;
};
```

We calculate the hash value of the key we want the value of and then traverse the linked list until it is either the end (or NULL) or we have found the key in the bucket.
Then we can either simply return "Not Found", or the value of the key.
