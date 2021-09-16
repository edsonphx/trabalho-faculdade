#ifndef repository_h
#define repository_h

#include "dataStructures.h"

struct Repository
{
    char* databasePath;
    struct Dictionary** (*select)(struct Repository* repository, char* table, int* outNumLines);
};

struct Repository repository_constructor(char* databasePath, int pathLength);

#endif