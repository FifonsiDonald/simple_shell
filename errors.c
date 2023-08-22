#include "shell.h"

/**
 * eputs - Prints a string to stderr.
 * @str: The string to be printed.
 */
void eputs(char *str)
{
    int i = 0;

    if (!str)
        return;

    while (str[i] != '\0')
    {
        eputchar(str[i]);
        i++;
    }
}

/**
 * eputchar - Writes a character to stderr.
 * @c: The character to be written.
 */
void eputchar(char c)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;
}

/**
 * putfd - Writes a character to the given file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 */
void putfd(char c, int fd)
{
    static int i = 0;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }

    if (c != BUF_FLUSH)
        buf[i++] = c;
}

/**
 * putsfd - Prints a string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 * @return: The number of characters written.
 */
int putsfd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;

    while (str[i])
    {
        putfd(str[i], fd);
        i++;
    }

    return i;
}
