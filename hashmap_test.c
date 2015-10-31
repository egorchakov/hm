#include <stdio.h>

#include "hashmap.h"

void print_hashmap(hm_t* hashmap) {
    int i;
    printf("\n=========================================================\n");
    printf("size: %d, capacity: %d\n", hashmap->size, hashmap->capacity);
    hm_entry_t* entry;
    for (i = 0; i < hashmap->capacity; i++){
        printf("%d -> ", i);
        entry = hashmap->buckets[i]; 
        while(entry != NULL) {
            printf("{key: %s, value: %d} -> ", entry->key, *(entry->val));
            entry = entry->next;
        }
        printf("<NULL>\n");
    }
    printf("\n=========================================================\n");
}

int main(void) {
    int size = 1 << 10;
    int i;
    int values[size];
    char keys[size][15];
    hm_t* hashmap = constructor(1 << 5);
    
    for (i = 0; i < size; i++) {
        values[i] = i;
        sprintf(keys[i], "key-%d", i);
    }
    
    printf("Setting values  ... ");
    for (i = 0; i < size; i++) assert(set(hashmap, keys[i], &values[i]));
    printf("PASS\n");

    printf("Getting values  ... ");
    for (i = 0; i < size; i++) assert(values[i] == *get(hashmap, keys[i])); 
    printf("PASS\n");

    printf("Deleting values ... ");
    for (i = 0; i < size; i++) {
        assert(values[i] == *delete(hashmap, keys[i]));
        assert(get(hashmap, keys[i]) == NULL);
    }
    printf("PASS\n");
    
    assert(load(hashmap) == (float)0);
    free(hashmap->buckets);
    free(hashmap);
}
