#include "headers.h"

#define BUFFER_SIZE 1024


void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;
	char *i, *j;

	if (new_size == old_size)
		return (ptr);
	if(new_size > 0 && (ptr == NULL || new_size > old_size))
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
	}
	else
		new_ptr = ptr;

	if (ptr != 0 && new_size > 0)
	{
		i = new_ptr;
		j = ptr;

		if (old_size > new_size)
		{
			old_size = new_size;
		}
		while (old_size)
		{
			old_size--;
			*i++ = *j++;
		}
	}
	free(ptr);
	return (new_ptr);

}

ssize_t _getline(char **line, size_t *len, FILE *stream)
{
	char *getline;
	ssize_t read;

	if (*line == NULL || *len == 0)
	{
		*len = 1024;
		*line = malloc(*len);
		if (*line == NULL)
		{
			return (-1);
		}
	}

	getline = fgets(*line, *len, stream);
	if (getline != NULL)
	{
		read = _strlen(*line);

		if (read > 0 && (*line)[read - 1] == '\n')
		{
			(*line)[read - 1] = '\0';
			read--;
		}
		return (read);
	}
	else
	{
		return (-1);
	}
}

/*ssize_t _getline(char **lineptr, size_t *n, int fd)
  {
  static char buffer[BUFFER_SIZE];
  static size_t buf_pos = 0;
  static size_t buf_size = 0;
  size_t capacity = *n;
  size_t i = 0;
  int new_size = 1025;
  int old_size = 0;
  char *new_line;

  if (lineptr == NULL || n == NULL)
  {
  errno = EINVAL;
  return (-1);
  }


  if (*lineptr == NULL || *n == 0)
  {
 *n = 128;
 *lineptr = (char *)malloc(capacity);
 if (*lineptr == NULL)
 return (-1);
 }

 while(1)
 {
 if (buf_pos >= buf_size)
 {
 buf_pos = 0;
 buf_size = read(fd, buffer, BUFFER_SIZE);
 }
 if (buf_size ==0)
 {
 if (i == 0)
 return (-1);
 break;
 }
 if (buf_size == SIZE_MAX)
 return (-1);
 (*lineptr)[i++] = buffer[buf_pos++];

 if (i >= *n - 1)
 {
 old_size = new_size;
 new_size = new_size + 1024;
 new_line = _realloc(*lineptr, old_size, new_size);
 *n *= 2;
 if (new_line == NULL)
 {
 free(*lineptr);
 return (-1);
 }
 *lineptr = new_line;

 }
 if (buffer[buf_pos - 1] == '\n')
 break;
 }
 (*lineptr)[i] = '\0';
 return (i);

 }*/
