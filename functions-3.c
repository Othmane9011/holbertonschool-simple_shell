#include "main.h"

/**
 * tokenize - tokenize the line
 * @line: line to be tokenized
 *
 * Return: argv pointer
 */

char **tokenize(char *line)
{
	int tok_size = 64;
	char *token = NULL;
	char **argv = NULL;
	int index = 0;

	argv = malloc(tok_size * sizeof(char *));

	if (argv == NULL)
	{
		perror("Error : allocation memory");
		free(argv);
		free(line);
		exit(1);
	}
	token = strtok(line, " ");

	while (token != NULL)
	{
		argv[index] = token;
		index++;
		token = strtok(NULL, " ");
	}
	argv[index] = NULL;

	return (argv);
}

/**
 * exec - function that executes the commands
 *
 * @args: array that lists commands
 *
 * Return: 1.
 */
int exec(char **args)
{
	pid_t my_pid;
	char *command = args[0];
	int status;

	my_pid = fork();

	if (my_pid == -1)
		perror("Error : fork");

	if (my_pid == 0)
	{
		if (command[0] == '/' || command[0] == '.')
		{
			command = args[0];
		}
		else
			perror("Eroor : no argument");

		if (args[0] == NULL)
			perror("Error : no argument");

		if (command == NULL)
		{
			free(command);
			perror("Error: no command");
			return (0);
		}
		if (execve(command, args, NULL) == -1)
		{
			perror("Error: execve");
			return (0);
		}
	}
	else
		wait(&status);

	return (1);
}

/**
 * _signal - Checks if a signal is in input.
 *
 * @sig: Input signal value.
 */

void _signal(int sig)
{
	if (sig == SIGINT)
		write(1, "\n salam aleikoum \n", 24);
}

/**
 * f_read - function that reads the user input
 *
 * Return: line if success or NULL if it fails
 */

char *f_read(void)
{
	char *line = NULL;
	size_t size = 0;
	ssize_t length = 0;

	length = getline(&line, &size, stdin);

	if (length == -1 || _strcmp(line, "exit\n") == 0)
	{
		free(line);
		exit(0);
	}
	if (line[length - 1] == '\n' && line[1] != '\0')
	{
		line[length - 1] = '\0';
	}
	return (line);
}
