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
	extern char **environ;
	if (_strcmp(av[0], "env") == 0)
	{
		int i = 0;

		for (; environ[i]; i++)
		{
			write(1, environ[i], _strlen(environ[i]));
			write(1, "\n", 1);
		}
		free(av);
	}
}
