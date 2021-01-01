/* API
 * - search(a, k): return value 'v' associated with key 'k'
 *   from the associative aray 'a', or NULL if the key doesn't exist
 * - insert(a, k, v): store pair 'k:v' in the associative array 'a'
 * - delete(a, k): delete the 'k:v' pair associated with 'k',
 *   or do nothing if 'k' does not exist
 */ 

#include "hash_table.h"

int main(void) {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);

    return 0;
}
