#ifndef dictionary_h
#define dictionary_h

#include "entry.h"

struct Dictionary 
{
	void (*insert)(struct Dictionary* dict, void* key, int keyLen, void* value, int valueLen);
	void* (*get)(struct Dictionary* dict, void* key);
	void (*remove)(struct Dictionary* dict, void* key);
	void (*update)(struct Dictionary* dict, void* key, void* value, int valueLen);
	void** (*get_keys)(struct Dictionary* dict);

	int (*compare)(void* firstKey, void* secondKey);

	int numKeys;
	struct Entry* lastEntry;
};

struct Dictionary* dictionary_constructor(int (*compare)(void* firstKey, void* secondKey));

void dictionary_destructor(struct Dictionary* dict);

#endif
