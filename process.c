#include "main.h"

void _freeArg(char **args, char **fptr);
char *get_pid(void);
char *env_val(char *_start, int len);
void _repvar(char **args, int *exe_ret);

/**
 * _freeArg - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @fptr: A double pointer to the _start of args.
 */
void _freeArg(char **args, char **fptr)
{
	size_t x;

	for (x = 0; args[x] || args[x + 1]; x++)
		free(args[x]);

	free(fptr);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a bsize and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t x = 0;
	char *bsize;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	bsize = malloc(120);
	if (!bsize)
	{
		close(file);
		return (NULL);
	}
	read(file, bsize, 120);
	while (bsize[i] != ' ')
		i++;
	bsize[i] = '\0';

	close(file);
	return (bsize);
}

/**
 * env_val - Gets the value corresponding to an environmental variable.
 * @_start: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *env_val(char *_start, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, _start, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(_strlen(temp) + 1);
		if (replacement)
			_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * _repvar - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void _repvar(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *nline;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = _itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = env_val(&old_line[j + 1], len);
			}
			nline = malloc(j + _strlen(replacement)
					  + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			nline[0] = '\0';
			_strncat(nline, old_line, j);
			if (replacement)
			{
				_strcat(nline, replacement);
				free(replacement);
				replacement = NULL;
			}
			_strcat(nline, &old_line[k]);
			free(old_line);
			*line = nline;
			old_line = nline;
			j = -1;
		}
	}
}