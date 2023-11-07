#include "headers.h"
/*
 * contains some functions we will use in the main.c
 * file since we can not use the standard
 * C function and libraries for the simple_shell project
 **/




/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(const char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * _strcspn - calculates the length of the initial
 * segment of a string that does not contain any of
 * a set of specified characters.
 * @str: string one
 * @chars: loc of strings
 *
 * Return: count
 */
size_t _strcspn(const char *str, const char *chars)
{
	const char *s1 = str;
	size_t i = 0;

	while (*s1)
	{
		const char *s2 = chars;

		while (*s2)
		{
			if (*s1 == *s2)
			{
				return (i);
			}
			s2++;
		}
		s1++;
		i++;
	}
	return (i);
}
