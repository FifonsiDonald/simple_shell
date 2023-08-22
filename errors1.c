#include "shell.h"

/**
 * err_atoi - Converts a string to an integer with error handling.
 * @s: The string to be converted.
 * Return: The converted number on success, or -1 on error.
 */
int err_atoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1; // Integer overflow
        }
        else
        {
            return -1; // Invalid character encountered
        }
    }
    return (int)result;
}

/**
 * print_error - Prints an error message.
 * @info: The info structure.
 * @estr: The error message.
 */
void print_error(info_t *info, char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_decimal - Prints a decimal (integer) number (base 10).
 * @input: The number to be printed.
 * @fd: The file descriptor to write to.
 * Return: The number of characters printed.
 */
int print_decimal(int input, int fd)
{
    int (*print_char)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
    int count = 0;
    unsigned int abs_input, current;

    if (input < 0)
    {
        abs_input = -input;
        print_char('-');
        count++;
    }
    else
    {
        abs_input = input;
    }

    current = abs_input;
    // ... (rest of the function implementation)

    return count;
}

