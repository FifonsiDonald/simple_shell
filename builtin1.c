#include "shell.h"

/**
 * print_alias_entry - prints a single alias entry.
 * @alias_entry: The alias entry to be printed.
 */
void print_alias_entry(list_t *alias_entry)
{
    char *p = NULL;

    if (alias_entry)
    {
        p = _strchr(alias_entry->str, '=');
        for (char *a = alias_entry->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
    }
}

/**
 * _myalias - Implements the alias command.
 * @info: Structure containing potential arguments.
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
    if (info->argc == 1)
    {
        list_t *alias_entry = info->alias;
        while (alias_entry)
        {
            print_alias_entry(alias_entry);
            alias_entry = alias_entry->next;
        }
        return 0;
    }

    for (int i = 1; info->argv[i]; i++)
    {
        char *p = _strchr(info->argv[i], '=');
        if (p)
        {
            set_alias(info, info->argv[i]);
        }
        else
        {
            list_t *alias_entry = node_starts_with(info->alias, info->argv[i], '=');
            print_alias_entry(alias_entry);
        }
    }

    return 0;
}
