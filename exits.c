#include "shell.h"

/**
 * _strncpy - Copies a string.
 * @dest: The destination string to be copied to.
 * @src: The source string.
 * @n: The number of characters to be copied.
 * Return: A pointer to the concatenated string.
 */
char *_strncpy(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    for (i = 0; src[i] != '\0' && i < n - 1; i++)
    {
        dest[i] = src[i];
    }

    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }

    return s;
}

/**
 * _strncat - Concatenates two strings.
 * @dest: The first string.
 * @src: The second string.
 * @n: The maximum number of bytes to be used from src.
 * Return: A pointer to the concatenated string.
 */
char *_strncat(char *dest, char *src, int n)
{
    int i, j;
    char *s = dest;

    for (i = 0; dest[i] != '\0'; i++)
    {
    }

    for (j = 0; src[j] != '\0' && j < n; i++, j++)
    {
        dest[i] = src[j];
    }

    dest[i] = '\0';

    return s;
}

/**
 * _strchr - Locates a character in a string.
 * @s: The string to be parsed.
 * @c: The character to look for.
 * Return: A pointer to the first occurrence of c in s, or NULL if not found.
 */
char *_strchr(char *s, char c)
{
    if (s == NULL)
    {
        return NULL;
    }

    do
    {
        if (*s == c)
        {
            return s;
        }
    } while (*s++ != '\0');

    return NULL;
}
