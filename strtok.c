#include "headers.h"
char *_strtok(char *str, const char *delim)
{
        static char *next_search;
/*      char i;*/
        char *ret;
        if (!str)
        {
                str = next_search;
        }
        if (!str)
                return (NULL);
        while (*str != '\0')
        {
                int isD = 0,i;
                for (i = 0; delim[i] != '\0'; i++)
                {
                        if (*str == delim[i])
                        {
                                isD = 1;
                                break;
                        }
                }
                if (!isD)
                {
                        break;
                }
                str++;
        }
         ret = str;
        while (*str != '\0')
        {
                int isD = 0, i;
                for (i = 0; delim[i] != '\0'; i++)
                {
                        if (*str == delim[i])
                        {
                                isD = 1;
                                break;
                        }
                }

                if (isD)
                {
                        *str = '\0';
                        next_search = str + 1;
                        return (ret);
                }
                str++;
        }
        next_search = str;
        return (ret);
}
