#include "hashmap.h"

/* The djb2 hash algorithm implementation is taken from 
 * http://www.cse.yorku.ca/~oz/hash.html
 */ 
static unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    
    return hash;
}

static unsigned int get_bucket_index(hm_t* hashmap, hm_key_t key) {
   return hash(key) % (hashmap->capacity);
}

hm_t* constructor(unsigned int capacity) {
    hm_entry_t** buckets = calloc(capacity, sizeof(hm_entry_t*)); 
    assert(buckets != NULL);

    hm_t* hashmap = malloc(sizeof(hm_t));
    assert(hashmap != NULL);

    hashmap->buckets = buckets;
    hashmap->capacity = capacity;
    hashmap->size = 0;
    
    return hashmap;
}

bool set(hm_t* hashmap, hm_key_t key, hm_val_t val) {
    unsigned int bucket_index = get_bucket_index(hashmap, key);
    hm_entry_t* entry = hashmap->buckets[bucket_index];
    
    while (entry != NULL && entry->key != key){
        entry = entry->next;
    }

    if (entry != NULL) {
        entry->val = val; 
    } else {
        hm_entry_t* new_entry = malloc(sizeof(hm_entry_t));
        if (new_entry == NULL) return false;

        new_entry->key = key;
        new_entry->val = val;
        new_entry->next = hashmap->buckets[bucket_index];
        
        if (new_entry->next == NULL) hashmap->size++;
        hashmap->buckets[bucket_index] = new_entry;
    } 
    return true;
}

hm_val_t get(hm_t* hashmap, hm_key_t key) {
    unsigned int bucket_index = get_bucket_index(hashmap, key); 
    hm_entry_t* entry = hashmap->buckets[bucket_index];
    
    while (entry != NULL && entry->key != key) {
       entry = entry->next; 
    }

    return entry != NULL ? entry->val : NULL;
}

hm_val_t delete(hm_t* hashmap, hm_key_t key) {
    unsigned int bucket_index = get_bucket_index(hashmap, key);
    hm_entry_t* entry = hashmap->buckets[bucket_index];
    hm_entry_t* next;
    hm_val_t val;
    
    // Case 1: No such entry exists
    if (entry == NULL) return NULL;

    // Case 2: First entry is to be deleted
    if (entry->key == key) {
        next = entry->next;
        hashmap->buckets[bucket_index] = next;
        if (next == NULL) (hashmap->size)--;
        val = entry->val;
        free(entry);
        return val;
    }
    // Case 3: Keep looking further down the linked list
    while (entry->next != NULL && entry->next->key != key) {
        entry = entry->next;
    }

    if (entry->next != NULL) {
        // Case 3.a: Found the parent of the entry to be deleted
        next = entry->next;
        val = next->val;
        entry->next = entry->next->next;
        free(next);

    } else {
        // Case 3.b: No entry found in this linked list
        val = NULL;
    }

    return val; 
}

float load(hm_t* hashmap) {
    return (float)hashmap->size / (float)hashmap->capacity;
}

