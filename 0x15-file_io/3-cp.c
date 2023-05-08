#include "main.h"
#include <stdio.h>
#include <stdlib.h>
char *create_buffer(char *file);
void close_file(int fd);
/**
 * create_buffer - Allocates 1024 bytes for a buffer.
 * @file: it is the name of the file buffer is storing chars for.
 * Return: it returns the pointer to the newly-allocated buffer.
 */
char *create_buffer(char *file)
{
	char *buffer;
	buffer = malloc(sizeof(char) * 1024);
	if (buffer == NULL)
	{
		dprintf(STDERR_FILENO,
		"Error: Can't write to %s\n", file);
		exit(99);
	}
	return (buffer);
}
/**
 * close_file - It closes the file descriptors.
 * @fd: The file descriptor which is to be closed.
 */
void close_file(int fd)
{
	int c;
	c = close(fd);
	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}
/**
 * main - Copies the contents of a file to another file.
 * @argc: The number of arguments which is supplied to the program.
 * @argv: it is an array of pointers to the arguments.
 * Return: on success it returns 0.
 * Description: If the argument counts is not correct - it exits code 97.
 * If the file_from does not exist or cannot be read -it  exits code 98.
 * If the file_to cannot be created or cannot be written to - exit code 99.
 * If the file_to or the file_from cannot be closed - exist the code 100.
 */
int main(int argc, char *argv[])
{
	int from, to, r, w;
	char *buffer;
	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	buffer = create_buffer(argv[2]);
	from = open(argv[1], O_RDONLY);
	r = read(from, buffer, 1024);
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	do {
		if (from == -1 || r == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			free(buffer);
			exit(98);
		}
		w = write(to, buffer, r);
		if (to == -1 || w == -1)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
			free(buffer);
			exit(99);
		}
		r = read(from, buffer, 1024);
		to = open(argv[2], O_WRONLY | O_APPEND);
	} while (r > 0);
	free(buffer);
	close_file(from);
	close_file(to);
	return (0);
}
