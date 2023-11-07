#include "headers.h"

void env()
{
	extern char **environ;
	char **env;
	for(env = environ; *env != NULL; env++)
	{
		write(STDOUT_FILENO, *env, _strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
	}
}
void run_env(char **av)
{
	if (strcmp(av[0], "env") == 0)
	{
		env();
	}
}
