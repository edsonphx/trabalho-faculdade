#include "repository.h"
#include "functions.h"
#include "dataStructures.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BYTES_PER_LINE 256

int compare(void* firstKey, void* secondKey);
struct Dictionary** select(struct Repository* repository, char* table, int* outNumLines);
int repo_insert(struct Repository* repository, char* table, struct Dictionary* data);

struct Repository repository_constructor(char* databasePath, int pathLength)
{
    struct Repository result;

    result.databasePath = memcpy(malloc(pathLength), databasePath, pathLength);
    result.select = select;
	result.insert = repo_insert;

    return result;
}

void repository_destructor(struct Repository* repository)
{
    free(repository->databasePath);
    free(repository->select);
    free(repository);
}

int repo_insert(struct Repository* repository, char* table, struct Dictionary* data)
{
	char tablename[256];

	sprintf(tablename, "%s\\%s\\data.csv",repository->databasePath, table);

	FILE* file = fopen(tablename, "a+");
    	if (file == NULL)
    	{
        	printf("Invalid path %s.\n", tablename);
        	return 0;
    	}

	int headersNum = 0;

	char* line = (char*)malloc(BYTES_PER_LINE);
	fgets(line, BYTES_PER_LINE, file);

	char** headers = split_string(line, ',', &headersNum);

	fseek(file, 0, SEEK_END);

	fprintf(file, "\n");

	for (int i = 0; i < headersNum; i++)
	{
		if (i+1 >= headersNum)
		{
			fprintf(file, "%s", data->get(data, (void*)headers[i]));
			continue;
		}

		fprintf(file, "%s,", data->get(data, (void*)headers[i]));
	}
	
	return 1;
}

struct Dictionary** select(struct Repository* repository, char* table, int* outNumLines)
{
	char tablename[256];

	sprintf(tablename, "%s\\%s\\data.csv",repository->databasePath, table);

	FILE* file = fopen(tablename, "a+");
    	if (file == NULL)
    	{
        	printf("Invalid path %s.\n", tablename);
        	return NULL;
    	}

	char* line = (char*)malloc(BYTES_PER_LINE);

	int linesRead = 0;

	int numLines = 0;
	for (char c = getc(file); c > EOF; c = getc(file))
        if (c == '\n')
            numLines++;

	if (outNumLines)
		*outNumLines = numLines;

	fseek(file, 0, SEEK_SET);

	char** headers = NULL;
	int headersNum = 0;

	struct Dictionary** result = malloc(sizeof(struct Dictionary*) * numLines);
	int resultIndex = 0;
    	while (fgets(line, BYTES_PER_LINE, file)) 
	{
		if (linesRead == 0)
		{
			headers = split_string(line, ',', &headersNum);
		}
		else
		{
			char** wordPointers = split_string(line, ',', NULL);

			result[resultIndex] = dictionary_constructor(NULL);

			struct Dictionary* dict = result[resultIndex];
			for (int i = 0; i < headersNum; i++)
			{
				char* key = headers[i];
				int keyLen = strlen(key) + 1;

				char* value = wordPointers[i];
				int valueLen = strlen(value) + 1;

				dict->insert(dict, key, keyLen, value, valueLen);
			}

			resultIndex++;
		}

		linesRead++;
    }

	fclose(file);

	return result;
}