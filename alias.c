/*
 *handling all the aliases here
 *including built in
 */

#include "main.h"

int sh_alias(char **args, char __attribute__((__unused__)) **front);
void createAlias(char *var_name, char *val);
void showalias(alias_t *alias);

/**
 * sh_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int sh_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *alptr = aliases;
	int x, ret = 0;
	char *val;

	if (!args[0])
	{
		while (alptr)
		{
			showalias(alptr);
			alptr = alptr->next;
		}
		return (ret);
	}
	for (x = 0; args[x]; x++)
	{
		alptr = aliases;
		val = _strchr(args[x], '=');
		if (!val)
		{
			while (alptr)
			{
				if (_strcmp(args[x], alptr->name) == 0)
				{
					showalias(alptr);
					break;
				}
				alptr = alptr->next;
			}
			if (!alptr)
				ret = create_error(args + x, 1);
		}
		else
			createAlias(args[x], val);
	}
	return (ret);
}

/**
 * createAlias - Will either set an existing alias 'name' with a new val,
 * 'val' or creates a new alias with 'name' and 'val'.
 * @var_name: Name of the alias.
 * @val: val of the alias. First character is a '='.
 */
void createAlias(char *var_name, char *val)
{
	alias_t *alptr = aliases;
	int len, j, k;
	char *new_val;

	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	new_val = malloc(sizeof(char) * (len + 1));
	if (!new_val)
		return;
	for (j = 0, k = 0; val[j]; j++)
	{
		if (val[j] != '\'' && val[j] != '"')
			new_val[k++] = val[j];
	}
	new_val[k] = '\0';
	while (alptr)
	{
		if (_strcmp(var_name, alptr->name) == 0)
		{
			free(alptr->val);
			alptr->val = new_val;
			break;
		}
		alptr = alptr->next;
	}
	if (!alptr)
		add_alias_end(&aliases, var_name, new_val);
}

/**
 * showalias - Prints the alias in the format name='val'.
 * @alias: Pointer to an alias.
 */
void showalias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->val) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->val);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their val.
 * @args: 2D pointer to the arguments.
 *
 * return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *alptr;
	int i;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		alptr = aliases;
		while (alptr)
		{
			if (_strcmp(args[i], alptr->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(alptr->val) + 1));
				if (!new_val)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_val, alptr->val);
				free(args[i]);
				args[i] = new_val;
				i--;
				break;
			}
			alptr = alptr->next;
		}
	}

	return (args);
}
