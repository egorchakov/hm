#ifndef __HASHMAP_H__
#define __HASHMAP_H__

#include <stdlib.h>
#include <stdio.h> 
#include <assert.h> 

typedef enum { false, true } bool;
typedef char* hm_key_t; 
typedef int* hm_val_t; 

struct hm_entry_s {
    hm_key_t key;
    hm_val_t val;
    struct hm_entry_s* next;
};

typedef struct hm_entry_s hm_entry_t;

typedef struct {
    hm_entry_t** buckets;
    unsigned int size;
    unsigned int capacity;
} hm_t;

/* API */
hm_t*       constructor     (unsigned int);
bool        set             (hm_t*, hm_key_t, hm_val_t);
hm_val_t    get             (hm_t*, hm_key_t);
hm_val_t    delete          (hm_t*, hm_key_t);
float       load            (hm_t*);

#endif
