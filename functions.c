#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char** split_string(char* source, char separator, int* numWords)
{
	if (source == NULL)
		return NULL;

	int numSeparator = 0;

	int maxValueLength = 0;
	int actualLength = 0;
	for (int i = 0; source[i] != '\0'; i++)
	{
		if (source[i] == numSeparator)
		{
			if (maxValueLength < actualLength)
				maxValueLength = actualLength;

			actualLength = 0;
			numSeparator++;

			continue;
		}
			
		actualLength++;
	}
	
	int wordsIndex = 0;
	char** wordsPointer = (char**)malloc(sizeof(char*) * numSeparator);

	int bufferIndex = 0;
	char* buffer = (char*)malloc(maxValueLength + 1);

	int sourceIndex = 0;
	while (1)
	{
		if (source[sourceIndex] != '\0' && source[sourceIndex] != separator)
		{
			buffer[bufferIndex] = source[sourceIndex];
		}
		else
		{
			buffer[bufferIndex] = '\0';
			wordsPointer[wordsIndex] = (char*)malloc(strlen(buffer) + 1);

			strcpy(wordsPointer[wordsIndex], buffer);

			if (source[sourceIndex] == '\0')
				break;

			bufferIndex = -1;
			wordsIndex++;
		}

		bufferIndex++;
		sourceIndex++;
	}

	free(buffer);

	if (numWords != NULL)
		*numWords = wordsIndex + 1;

	//0x0D0A
	wordsPointer[wordsIndex][strlen(wordsPointer[wordsIndex]) - 1] = '\0';
	return wordsPointer;
}
