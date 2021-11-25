#include <stdio.h>
#include <string.h>
#include "dataStructures.h"
#include "repository.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("[Usage] program.exe C:/users/user/document/database");
		return 1;
	}	

	char* path = argv[1];

	struct Repository repository = repository_constructor(path, strlen(path) + 1);
	
	int n = 0;
	struct Dictionary** values = repository.select(&repository, "Users", &n);

	char name[32];
	printf("\nDigite o nome de usuario: ");
	scanf("%s", &name);

	fflush(stdin);

	for (int i = 0; i < n; i++)
	{
		struct Dictionary* data = values[i];
		if (strcmp((char*)data->get(data, "user"), (char*)name) == 0)
		{
			char password[32];
			printf("\nDigite sua senha: ");
			scanf("%s", &password);

			if (strcmp((char*)data->get(data, "password"), (char*)password) == 0)
			{
				printf("\n\nLogado");

				//inserindo dados
				struct Dictionary* newUser = dictionary_constructor(NULL);

				newUser->insert(newUser, "user", 5, "user", 5);
				newUser->insert(newUser, "password", 9, "test", 5);

				repository.insert(&repository, "Users", newUser);
				//
			}
			else
			{
				printf("\n\nMorra Hacker");
			}
		}
	}

	return 0;
}