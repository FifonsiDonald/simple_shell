#include "headers.h"
#include <sys/stat.h>


/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * cmdexec - Execute a command with its arguments.
 * @av: A NULL-terminated array of strings
 * representing the command and its arguments.
 *
 * If the execution fails, an error message is printed
 * to stderr, and the program exits
 * with a failure status.
 */
void cmdexec(char **av)
{
	char *cmd = NULL;

	if (av)
	{
		if (av[0][0] == '/')
		{
			cmd = av[0];

			if (cmd == NULL)
			{
				perror("Command not found");
				return;
			}
		}
		else
		{
			cmd = get_path(av[0]);
		}

		if (execve(cmd, av, NULL) == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * get_path - Find the full path of a command in
 * the PATH environment variable.
 * @cmd: The name of the command to search for.
 *
 * Return: A dynamically allocated string containing
 * the full path of the command if
 * found, or NULL if not found.
 */
char *get_path(char *cmd)
{
	struct stat buffer;
	char *path, *file_path, *path_token, *dup_path;
	int cmdlen, dir_len, fpm;

	path = getenv("PATH");
	if (path)
	{
		dup_path = _strdup(getenv("PATH"));
		path_token = _strtok(dup_path, ":");
		cmdlen = _strlen(cmd);

		while (path_token)
		{
			dir_len = _strlen(path_token);
			fpm = cmdlen + dir_len + 2;
			file_path = malloc(fpm);

			_strcpy(file_path, path_token);
			_strcat(file_path, "/");
			_strcat(file_path, cmd);
			_strcat(file_path, "\0");

			if (stat(file_path, &buffer) == 0)
			{
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = _strtok(NULL, ":");
			}
		}
		return (NULL);
	}
	return (NULL);
}
