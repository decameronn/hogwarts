 
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

/* Initialization for ht_item:
 * - allocate required memory
 * - save a copy of k & v strings in memory
 */
static ht_item* ht_new_item(const char* k, const char* v) {
    ht_item* i = malloc(sizeof(ht_item));
    i->k = strdup(k);
    i->v = strdup(v);
    return i;
}

/* Initialize a new hash table.
 * - size: how many items we can store
 * - calloc to fill everything with NUL bytes
 */
ht_hash_table* ht_new(void) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->size = 53; /* fixed for now */
    ht->count = 0;
    ht->items = calloc((size_t)ht->table, sizeof(ht_item*));
    return ht;
}





