#include "headers.h"


int main(int ac, char **av)
{
	int exit_status;
	char cwd[1024];
	char *lineptr;
	size_t n=0;
	ssize_t chars_got;
	char *copy = NULL;
	const char *delim = " \n";
	char *token;
	int counter = 0;
	int i;
	pid_t pid;
	(void)ac;
	exit_status = 0;

	if (isatty(STDIN_FILENO))
	{

		getcwd(cwd, sizeof(cwd));

		while (1)
		{
			char prompt[] = "#cisfun$ ";
			char byeprompt[] = "Goodbye!...";
			char newline[] = " \n";
			write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
			fflush(stdout);

			chars_got = _getline(&lineptr, &n, fileno(stdin));

			if (chars_got == -1)
			{
				write(STDOUT_FILENO, newline, sizeof(newline) - 1);

				write(STDOUT_FILENO, byeprompt, sizeof(byeprompt) - 1);

				write(STDOUT_FILENO, newline, sizeof(newline) - 1);

				return (-1);
			}
			lineptr[_strcspn(lineptr, "\n")] = '\0';

			copy = malloc(sizeof(char) * chars_got);

			if (copy == NULL)
			{
				return (-1);
			}
			_strcpy(copy, lineptr);
			token = strtok(copy, delim);

			while (token != NULL)
			{
				counter++;
				token = strtok(NULL, delim);
			}
			counter++;
			av = malloc(sizeof(char *) * counter);
			token = strtok(lineptr, delim);

			for (i = 0; token != NULL; i++)
			{
				av[i] = malloc(sizeof(char) * _strlen(token));
				_strcpy(av[i], token);

				token = strtok(NULL, delim);
			}
			av[i] = NULL;
			pid = fork();

			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}


			if (pid == 0)
			{
				cmdexec(av);
			}
			else
			{
				int status;
				/*int exit_status;*/
				if ( _strcmp(lineptr, "exit") == 0)
				{
					free(lineptr);
					if (av[1] != NULL)
						exit_status = atoi(av[1]);
					exit(exit_status);
				}
				else if (_strcmp(lineptr, "setenv") == 0)
				{
					if (av[1] != NULL && av[2] != NULL && av[3] == NULL)
					{
						if (setenv(av[1], av[2], 1) != 0)
						{
							perror("setenv");
						}
					}
					else
					{
						write(STDERR_FILENO, "Usage: setenv VARIABLE\n", _strlen("Usage: setenv VARIABLE\n"));
					}
				}
				else if (_strcmp(av[0], "unsetenv") == 0)
				{
					if (av[1] != NULL && av[2] == NULL)
					{
						if (unsetenv(av[1]) != 0)
						{
							perror("unsetenv");
						}
					}
					else
					{
						write(STDERR_FILENO, "Usage: unsetenv VARIABLE\n", _strlen("Usage: unsetenv VARIABLE\n"));
					}
				}
				wait(&status);

				if (WIFEXITED(status))
				{
					int exit_status = WEXITSTATUS(status);
					if (exit_status != 0)
					{
						write(STDOUT_FILENO, "Command failed\n", _strlen("Command failed\n"));
					}
				}
			}

			run_env(av);
			free(copy);
			free(av);
		}
		return (exit_status);
	}
	else
	{
	}
	return (0);
}
