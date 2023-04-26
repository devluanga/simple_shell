/*this file will handle all the user inputs*/
#include "main.h"

void *__memoryAlloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assignPtr(char **lineptr, size_t *n, char *buffer, size_t b);
ssize_t _userInput(char **lineptr, size_t *n, FILE *stream);

/**
 * __memoryAlloc - Reallocates a _memoryory block using malloc and free.
 * @ptr: A pointer to the _memoryory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new _memoryory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated _memoryory block.
 */
void *__memoryAlloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *_memory;
	char *ptr_copy, *_fil;
	unsigned int value;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		_memory = malloc(new_size);
		if (_memory == NULL)
			return (NULL);

		return (_memory);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	ptr_copy = ptr;
	_memory = malloc(sizeof(*ptr_copy) * new_size);
	if (_memory == NULL)
	{
		free(ptr);
		return (NULL);
	}

	_fil = _memory;

	for (value = 0; value < old_size && value < new_size; value++)
		_fil[value] = *ptr_copy++;

	free(ptr);
	return (_memory);
}

/**
 * assignPtr - Reassigns the lineptr variable for _userInput.
 * @lineptr: A buffer to store an input string.
 * @n: The size of lineptr.
 * @buffer: The string to assign to lineptr.
 * @b: The size of buffer.
 */
void assignPtr(char **lineptr, size_t *n, char *buffer, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}

/**
 * _userInput - Reads input from a stream.
 * @lineptr: A buffer to store the input.
 * @n: The size of lineptr.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _userInput(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buffer;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * 120);
	if (!buffer)
		return (-1);

	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}

		if (input >= 120)
			buffer = __memoryAlloc(buffer, input, input + 1);

		buffer[input] = c;
		input++;
	}
	buffer[input] = '\0';

	assignPtr(lineptr, n, buffer, input);

	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}