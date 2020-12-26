#ifndef HASH_TABLE
#define HASH_TABLE

/* k:v */
typedef struct {
    char* key;
    char* value;
} ht_item;

/* hash table */
typedef struct {
    int size;
    int count;
    ht_item* items;
} ht_hash_table;


#endif /* !HASH_TABLE */
