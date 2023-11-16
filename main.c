#include "headers.h"

void change_dir(char *dir)
{
	char *home = getenv("HOME");
	char *previous_directory = getenv("OLDPWD");
	char current_directory[1024];
	/*char *home_path = NULL;*/

	if (dir == NULL)
	{
		dir = home;
	}
	else if (_strcmp(dir, "-") == 0)
	{
		dir = previous_directory;
		printf("%s\n", dir);
	}

	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		perror("getcwd() error");
		return;
	}

	if (chdir(dir) == -1)
	{
		perror("chdir() error");
		return;
	}

	setenv("OLDPWD", current_directory, 1);
	if (getcwd(current_directory, sizeof(current_directory)) == NULL)
	{
		perror("getcwd() error");
	}
	else
	{
		setenv("PWD", current_directory, 1);
	}

	/*	if (home != NULL) {
		home_path = malloc(strlen(home) + 1);
		if (home_path == NULL) {
		perror("malloc");
		exit(EXIT_FAILURE);
		}
		_strcpy(home_path, home);
		}
		else
		{
		fprintf(stderr, "HOME environment variable is not set.\n");
		exit(EXIT_FAILURE);
		}



		if(dir == NULL)
		{
		if(chdir(home_path) != 0)
		{
		perror("chdir");
		}
		}
		else
		{
		if (chdir(dir) != 0)
		{
		perror("chdir");
		}
		}
		free(home_path);*/
}


int main(int ac, char **av)
{
	int status;
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

			/*while (token != NULL)
			{
				counter++;
				token = strtok(NULL, delim);
				if (strcmp(token, "cd") != 0)
                                {
                                        char *dirh = strtok(NULL, " ");
                                        change_dir(dirh);
                                }
                                else
                                {
                                        printf ("didn't work here else");
                                }
			}*/
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
					if ( _strcmp(lineptr, "exit") == 0)
					{
						free(lineptr);
						if (av[1] != NULL)
							exit_status = atoi(av[1]);
						exit(exit_status);
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
				run_env(av);
			}

			free(copy);
			free(av);
		}
		return (exit_status);
	}
	/*return (0);
	  }*/
