#include "headers.h"

/**
 * print_prompt -  Prints the command prompt.
 *
 * Return: print prompt.
 */
void print_prompt(void)
{
	char prompt[] = "#cisfun$ ";

	write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
	fflush(stdout);
}

/**
 * handle_input - Reads user input from standard input.
 *
 * @lineptr:lineptr Pointer to the buffer for storing the input line.
 * @n: Size of the buffer.
 * Return: input.
 */
void handle_input(char **lineptr, size_t *n)
{
	ssize_t chars_got = getline(lineptr, n, stdin);

	if (chars_got == -1)
	{
		write(STDOUT_FILENO, " \nGoodbye!...\n \n",
		sizeof(" \nGoodbye!...\n \n") - 1);
		exit(-1);
	}

	(*lineptr)[_strcspn(*lineptr, "\n")] = '\0';
}


/**
 * tokenize_input - Tokenizes the input line into command arguments.
 *
 * @lineptr: lineptr Input line to be tokenized.
 * @av: Pointer to the array of command arguments.
 * Return: tokenized input.
 */
void tokenize_input(char *lineptr, char ***av)
{
	int *counter;
	char *token = strtok(lineptr, " ");
	int i;

	while (token != NULL)
	{
		counter++;
		token = strtok(NULL, " ");
	}

	counter++;
	*av = malloc(sizeof(char *) * (*counter));

	token = strtok(lineptr, " ");

	for (i = 0; token != NULL; i++)
	{
		(*av)[i] = malloc(sizeof(char) * _strlen(token));
		_strcpy((*av)[i], token);
		token = strtok(NULL, " ");
	}

	(*av)[i] = NULL;
}
/**
 * execute_command - Executes a command with its arguments.
 *
 * @av: Array of command arguments.
 * @exit_status: Pointer to the exit status variable.
 * Return: executed commands.
 */
void execute_command(char **av, int *exit_status)
{
	pid_t pid = fork();

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
		if (_strcmp(av[0], "exit") == 0)
		{
			if (av[1] != NULL)
				*exit_status = atoi(av[1]);
			free(av[0]);
			av[0] = NULL;
			exit(*exit_status);
		}
	}
	wait(NULL);
}

/**
 * main - The main function of the program.
 *
 * Return: The exit status of the program.
 */
int main(void)
{
	/*int status;*/
	int exit_status = 0;
	char cwd[1024];
	char *lineptr = NULL;
	size_t n = 0;
	char *copy;
	char **command_args;
	/*int counter;*/

	if (isatty(STDIN_FILENO))
	{
		getcwd(cwd, sizeof(cwd));

		while (1)
		{

			print_prompt();
			handle_input(&lineptr, &n);

			copy = malloc(sizeof(char) * n);
			_strcpy(copy, lineptr);

			command_args = NULL;

			tokenize_input(copy, &command_args);

			execute_command(command_args, &exit_status);
			/*change_dir(command_args);*/

			if (exit_status != 0)
			{
				write(STDOUT_FILENO, "Command failed\n", _strlen("Command failed\n"));
			}
			run_env(command_args);
			free(copy);
		}
		free(lineptr);
	}
	return (exit_status);
}
