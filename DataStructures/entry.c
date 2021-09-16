#include "entry.h"
#include <string.h>
#include <stdlib.h>

struct Entry* entry_constructor(
    void* key,
    int keyLen,
    void* value,
    int valueLen,
    struct Entry* previousPtr, 
    struct Entry* nextPtr)
{
    if (key == NULL || value == NULL)
        return NULL;
        
    struct Entry* result = (struct Entry*)malloc(sizeof(struct Entry));

    result->key = memcpy(malloc(keyLen), key, keyLen);
    result->value = memcpy(malloc(valueLen), value, valueLen);

    result->previous = previousPtr;
    result->next = nextPtr;

    return result;
}

void entry_destructor(struct Entry* entry)
{
    free(entry->key);
    free(entry->value);
    free(entry);
}