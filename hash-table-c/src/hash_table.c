 
/* API
 * - search(a, k): return value 'v' associated with key 'k'
 *   from the associative aray 'a', or NULL if the key doesn't exist
 * - insert(a, k, v): store pair 'k:v' in the associative array 'a'
 * - delete(a, k): delete the 'k:v' pair associated with 'k',
 *   or do nothing if 'k' does not exist
 */ 

#include <stdlib.h>
#include <string.h>
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

/* Manually delete ht_item & ht_hash_table to avoid memory leaks */
static void ht_del_item(ht_item* i) {
    free(i->key);
    free(i->value);
    free(i);
}

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
