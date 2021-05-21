#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#include <conway.h>
#include <readfile.h>

char** init_matrix(char* filename, int* _y, int* _x)
{
	char** matrix = NULL;
	char* buffer;
	size_t y, x;

	buffer = read_file(filename);
	if (!buffer)
		return NULL;
	
	y = strocc(buffer, '\n') + 1;

	char* tmp = strchr(buffer, '\n');
	if (!tmp)
		x = strlen(buffer);
	else
		x = tmp - buffer;
	
	matrix = matrixdup(NULL, y, x);
	if (!matrix)
		goto free_buffer;
	
	canonicalize_buffer(buffer);
	for (size_t i = 0; i < y; i++) {
		for (size_t j = 0; j < x; j++) {
			matrix[i][j] = buffer[(x + 1) * i + j];
		}
	}
	
	*(_y) = y;
	if (_x)
		*(_x) = x;
free_buffer:
	free(buffer);
	return matrix;
}

off_t get_file_size(char* filename)
{
	struct stat st;

	if (stat(filename, &st) == -1)
		return -1;
	
	return st.st_size;
}

size_t strocc(const char* str, const char c)
{
	size_t counter = 0;

	for (size_t i = 0; str[i] != '\0'; i++)
		if (str[i] == c)
			counter++;
	
	return counter;
}

char* read_file(char* filename)
{
	FILE* file;
	char* buffer = NULL;
	off_t file_size;

	file = fopen(filename, "r");
	if (!file)
		return NULL;
	
	file_size = get_file_size(filename);
	if (file_size < 0)
		goto close_file;
	
	buffer = calloc(file_size + 1, 1);
	if (!buffer)
		goto close_file;
	
	if (!fread(buffer, 1, file_size, file)) {
		free(buffer);
		return NULL;
	}

close_file:
	fclose(file);
	return buffer;
}

void canonicalize_buffer(char* buffer)
{
	for (size_t i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] != '\n')
			buffer[i] -= '0';
}