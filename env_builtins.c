#include "headers.h"
 int setenv(const char *name, const char *value, int overwrite)
{
	size_t env_var_len;
	char *env_var;
	if (getenv(name) != NULL && !overwrite)
	{
		write(STDERR_FILENO, "Variable already exists and overwrite is not allowed.\n", _strlen("Variable already exists and overwrite is not allowed.\n"));
		return (-1);
	}
	env_var_len = strlen(name) + strlen(value) + 3;
	env_var = (char *)malloc(env_var_len);
	if (env_var == NULL)
	{
		perror ("malloc");
		return (-1);
	}
	if (putenv(env_var) != 0)
	{
		perror("putenv");
		free(env_var);
		return (-1);
	}
	return (0);
}

int unsetenv(const char *name)
{
	extern char **environ;
	char **env = environ;
	char **p;
	if (strlen(name) == 0)
	{
		write(STDERR_FILENO, "Invalid variable name.\n",_strlen("Invalid variable name.\n"));
		return (-1);
	}
	while (*env)
	{
		if(_strcmp(*env, name) == 0 && (*env)[_strlen(name)] == '=')
		{
			for (p = env; *p; ++p)
				*p = *(p + 1);
			return (0);
		}
		++env;
	}
	write(STDERR_FILENO, "Variable not found\n", _strlen("Variable not found"));
	return (-1);
}
