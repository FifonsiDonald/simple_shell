#include "shell.h"

/**
 * interactive - Checks if the shell is in interactive mode
 * @info: Pointer to struct address
 *
 * Return: 1 if interactive mode, 0 if not
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Checks if a character is a delimiter
 * @c: The character to check
 * @delim: The delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	if (!delim)
		return (0);

	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * is_alphabetic - Checks if a character is alphabetic
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int is_alphabetic(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * custom_atoi - Converts a string to an integer
 * @s: The string to be converted
 * Return: 0 if no numbers in the string, the converted number otherwise
 */
int custom_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
