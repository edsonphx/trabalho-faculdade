#include "dictionary.h"
#include <stdlib.h>
#include <string.h>

void insert(struct Dictionary* dict, void* key, int keyLen, void* value, int valueLen);
void* get(struct Dictionary* dict, void* key);
void remove(struct Dictionary* dict, void* key);
void update(struct Dictionary* dict, void* key, void* value, int valueLen);

int default_compare(void* firstKey, void* secondKey);

struct Dictionary* dictionary_constructor(int (*compare)(void* firstKey, void* secondKey))
{


    struct Dictionary* result = (struct Dictionary*)malloc(sizeof(struct Dictionary));

	if (compare != NULL)
        result->compare = compare;
	else
		result->compare = default_compare;
    
    result->lastEntry = NULL;
	
    result->insert = insert;
    result->get = get;
    result->update = update;
    result->remove = remove;

    return result;
}

void dictionary_destructor(struct Dictionary* dict)
{
	struct Entry* iterator = dict->lastEntry;
	while (iterator) 
	{
		if (iterator->next)
			free(iterator->next);

		free(iterator->key);
		free(iterator->value);

		iterator = iterator->previous;
	}
}
void insert(struct Dictionary* dict, void* key, int keyLen, void* value, int valueLen)
{
    if (key == NULL || value == NULL)
        return;

	if (dict->lastEntry != NULL) 
	{
		if (dict->get(dict, key) != NULL)
		    return;

		struct Entry* entry = entry_constructor(
            		key,
            		keyLen,
            		value,
            		valueLen, 
            		dict->lastEntry,
            		NULL);

		dict->lastEntry->next = entry;

		//now entry is the last entry
		dict->lastEntry = entry;
	}
	else 
	{
		dict->lastEntry = entry_constructor(key, keyLen, value, valueLen, NULL, NULL);
	}
}

void* get(struct Dictionary* dict, void* key)
{
    if (key == NULL)
	return NULL;

	struct Entry* iterator = dict->lastEntry;
	while (iterator) 
	{
		if (dict->compare(iterator->key, key))
			return iterator->value;

		iterator = iterator->previous;
	}

	return NULL;
}

void remove(struct Dictionary* dict, void* key)
{
    if (key == NULL)
	return;

	struct Entry* iterator = dict->lastEntry;
	while (iterator)
	{
		if (dict->compare(iterator->key, key))
		{
			if (iterator->previous)
				iterator->previous->next = iterator->next;

			if (iterator->next)
				iterator->next->previous = iterator->previous;
			else
				dict->lastEntry = iterator->previous;
			
			free(iterator);
			return;
		}

		iterator = iterator->previous;
	}
}

void update(struct Dictionary* dict, void* key, void* value, int valueLen)
{
	if (key == NULL || value == NULL)
		return;

	struct Entry* iterator = dict->lastEntry;
	while (iterator)
	{
		if (dict->compare(iterator->key, key))
		{
			free(iterator->value);
			iterator->value = memcpy(malloc(valueLen), value, valueLen);
		}
			
		iterator = iterator->previous;
	}
}

int default_compare(void* firstKey, void* secondKey)
{
	return strcmp((char*)firstKey,(char*)secondKey) == 0;
}