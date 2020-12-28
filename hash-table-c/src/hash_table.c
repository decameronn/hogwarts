
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"


/*  INITIALIZE AND DELETE */

/* Initialization for ht_item:
 * - allocate required memory
 * - save a copy of k & v strings in memory
 */
static ht_item* ht_new_item(const char* key, const char* value) {
    ht_item* i = malloc(sizeof(ht_item));
    i->key = strdup(key);
    i->value = strdup(value);
    return i;
}

/* Initialize a new hash table.
 * - size: how many items we can store
 * - calloc to fill everything with NULL bytes
 */
ht_hash_table* ht_new(void) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->size = 53; /* fixed for now */
    ht->count = 0;
    ht->items = calloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

/* Manually delete ht_item to avoid memory leaks */
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

/* Manually delete ht_hash_table to avoid memory leaks */
void ht_del_hash_table(ht_hash_table* ht) {
    int i;
    for (i = 0; i < ht->size; i++) {
	ht_item* item = ht->items[i];
	if (item != NULL) {
	    ht_del_item(item);
	}
    }
    free(ht->items);
    free(ht);
}


/* HASH FUNCTION ALGORITHM */

/* function hash(string, a, num_buckets):
 *     hash = 0
 *     string_len = length(string)
 *     for i = 0, 1, ..., string_len:
 *         hash += (a ** (string_len - (i+1))) * char_code(string[i])
 *     hash = hash % num_buckets
 *     return hash
 */
static int ht_hash(const char* s, const int a, const int m) {
    int i;
    long hash = 0;
    const int len_s = strlen(s);
    for (i = 0; i < len_s; i++) {
	hash += (long)pow(a, (len_s - (i+1))) * s[i];
	hash %= m;
    }
    return (int)hash;
}


/* HANDLING COLLISIONS - DOUBLE HASHING */

/* Double hashsing:
 * use two hash functions to calculate the index
 * an item should be stored at after i collisions.
 * 
 * index = (hash_a(s) + i * (hash_b(s) + 1)) % num_buckets
 */
static int ht_get_hash(const char* s, const int num_buckets, const int attempt) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);

    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}
