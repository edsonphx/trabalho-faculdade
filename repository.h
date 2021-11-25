#ifndef repository_h
#define repository_h

#include "dataStructures.h"

struct Repository
{
    char* databasePath;

    struct Dictionary** (*select)(
        struct Repository*
        repository, 
        char* table,
        int* outNumLines);

    int (*insert)(
        struct Repository* repository,
        char* table,
        struct Dictionary* data);
};

struct Repository repository_constructor(char* databasePath, int pathLength);

#endif