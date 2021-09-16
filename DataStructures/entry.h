#ifndef entry_h
#define entry_h

struct Entry 
{
    struct Entry* next;
	struct Entry* previous;
	void* key;
	void* value;
};

struct Entry* entry_constructor(
    void* key,
    int keyLen,
    void* value,
    int valueLen,
    struct Entry* previousPtr, 
    struct Entry* nextPtr);

void entry_destructor(struct Entry* entry);

#endif