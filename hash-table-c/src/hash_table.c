#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash_table.h"
#include "prime.h"

static ht_item HT_DELETED_ITEM = {NULL, NULL};

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
static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = xmalloc(sizeof(ht_hash_table));
    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = xcalloc((size_t)ht->size, sizeof(ht_item*));
    return ht;
}

ht_hash_table* ht_new(void) {
    return ht_new_sized(HT_INITAL_BASE_SIZE);
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

/* Resize:
 * - make sure not to reduce the size of hash table below its minimum
 * - init a new hash table with the desired size
 * - all 'deleted' items are inserted in the new hash table
 * - swap attributes of new & old tables before deleting the old
 */
static void ht_resize(ht_hash_table* ht, const int base_size) {

    if (base_size < HT_INITAL_BASE_SIZE) return;

    ht_hash_table* new_ht = ht_new_sized(base_size);
    int i;
    for (i = 0; i < ht->size; i++) {
	ht_item* item = ht->items[i];
	if (item != NULL && item != &HT_DELETED_ITEM) {
	    ht_insert(new_ht, item->key, item->value);
	}
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    /* delete new_ht */
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    ht_item** tmp_items = ht->items;
    ht->items = new_ht->items;
    new_ht->items = tmp_items;

    ht_del_hash_table(new_ht);
}

/* Simplify the resizing with Up and Down imlementations */
static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}
static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
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
    int index = (hash_a + (attempt * (hash_b + 1))) % num_buckets;
    return index;
}


/* API */

/* Insert Key:Value pair :
 * - iterate through indexes until we find an empty bucket
 * - insert k:v and increment 'count'
 */
void ht_insert(ht_hash_table* ht, const char* key, const char* value) {

    /* check the load on the table after insert (100/70 to avoid floats) */
    const int load = (ht->count * 100) / ht->size;  
    if (load > 70) ht_resize_up(ht);
    
    ht_item* item = ht_new_item(key, value);
    int index = ht_get_hash(item->key, ht->size, 0);
    ht_item* cur_item = ht->items[index];
    int i = 1;
    while (cur_item != NULL) {
	if (cur_item != &HT_DELETED_ITEM) {
	    if (strcmp(cur_item->key, key) == 0) {
		ht_del_item(cur_item);
		ht->items[index] = item;
		return;
	    }
	}
    }
    ht->items[index] = item;
    ht->count++;
}

/* Search:
 * - similar to Insert API
 * - if item's key matches the one we're looking for, we return the value
 */
char* ht_search(ht_hash_table* ht, const char* key) {
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
	if (item != &HT_DELETED_ITEM) {
	    if (strcmp(item->key, key) == 0) {
		return item->value;
	    }
	}
	index = ht_get_hash(key, ht->size, i);
	item = ht->items[index];
	i++;
    }
    return NULL;
}

/* Delete:
 * - beware: item we wish to delete may be a part of a collision chain
 * - remove it and it will brak the chain, thus finding the other items will be impossible
 * - solution: do not delete, MARK as deleted (replace with a pointer to a global sentinel)
 */
void ht_delete(ht_hash_table* ht, const char* key) {

    const int load = (ht->count * 100) / ht->size;
    if (load < 10) ht_resize_up(ht);
    
    int index = ht_get_hash(key, ht->size, 0);
    ht_item* item = ht->items[index];
    int i = 1;
    while (item != NULL) {
	if (item != &HT_DELETED_ITEM) {
	    if (strcmp(item->key, key) == 0) {
		ht_del_item(item);
		ht->items[index] = &HT_DELETED_ITEM;
	    }
	}
	index = ht_get_hash(key, ht->size, i);
	item = ht->items[index];
	i++;
    }
    ht->count--;
}


