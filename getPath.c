#include "main.h"

char *_pathdir(char *path);
list_t *_getpath(char *path);

/**
 * _getCom - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *_getCom(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = _getpath(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(command) + 2);
		if (!temp)
			return (NULL);

		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_list(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_list(head);

	return (NULL);
}

/**
 * _pathdir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *_pathdir(char *path)
{
	int i, length = 0;
	char *_cpath, *curredir;

	curredir = *(_getenv("curredir")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(curredir) + 1;
			else
				length++;
		}
		else
			length++;
	}
	_cpath = malloc(sizeof(char) * (length + 1));
	if (!_cpath)
		return (NULL);
	_cpath[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(_cpath, curredir);
				_strcat(_cpath, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(_cpath, ":");
				_strcat(_cpath, curredir);
			}
			else
				_strcat(_cpath, ":");
		}
		else
		{
			_strncat(_cpath, &path[i], 1);
		}
	}
	return (_cpath);
}

/**
 * _getpath - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *_getpath(char *path)
{
	int index;
	char **dirs, *_cpath;
	list_t *head = NULL;

	_cpath = _pathdir(path);
	if (!_cpath)
		return (NULL);
	dirs = _strtok(_cpath, ":");
	free(_cpath);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}