#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <include/conway.h>

void printmatrix(char** matrix, int y, int x)
{
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++)
			putc(matrix[i][j] ? '#' : ' ', stdout);
		putc('\n', stdout);
	}
}

int inbounds(int y, int x, int low_y, int low_x, int up_y, int up_x)
{
	return (y >= low_y && y < up_y && x >= low_x && x < up_x);
}

int cell_count(char **start, int y, int x, int low_y, int low_x, int up_y, int up_x)
{
    int neighbours = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if(i == 0 && j == 0)
				continue;
			
			if(inbounds(y+i, x+j, low_y, low_x, up_y, up_x))
				neighbours += start[y+i][x+j];
		}
	}

	return neighbours;
}

int cell_status(char **start, int y, int x, int up_y, int up_x)
{
	int neighbours;

	neighbours = cell_count(start, y, x, 0, 0, up_y, up_x);
	if (start[y][x])
		switch (neighbours) {
		case 2:
		case 3:
			return 1;
		default:
			return 0;
		}
	else
		switch (neighbours) {
		case 3:
			return 1;
		}
	
	return 0;
}

char **next_generation(char **start, char **cells, int *rowptr, int *colptr)
{
	char** tmp;
	int eq = (start == cells);
	int status;

	if (eq) {
		tmp = matrixdup(cells, *rowptr, *colptr);
		if (!tmp)
			return NULL;
	}

    for (int y = 0; y < *rowptr; y++) {
        for (int x = 0; x < *colptr; x++) {
			status = cell_status(start, y, x, *rowptr, *colptr);

			if (eq) tmp[y][x] = status;
			else  cells[y][x] = status;
		}	
    }

	if (eq) {
		for (int y = 0; y < *rowptr; y++)
			for (int x = 0; x < *colptr; x++)
				cells[y][x] = tmp[y][x];
		
		free_matrix(&tmp, *rowptr);
	}

    return cells;
}

void free_matrix(char ***matrix, int y)
{
    for (int i = 0; i < y; i++)
        free((*matrix)[i]);
  
    free(*matrix);
    *matrix = NULL;
}

char** matrixdup(char** src, int y, int x)
{
    char** matrix = malloc(y * sizeof(char*));
    if (!matrix)
        return NULL;
    
    for (int i = 0; i < y; i++) {
        matrix[i] = calloc(x, sizeof(char));
        if (!matrix) {
            free_matrix(&matrix, i);
            return NULL;
        }

		if (src)
			memmove(matrix[i], src[i], x * sizeof(char));
		
    }
    return matrix; 
}

void matrixcpy(char** dest, char** src, int y, int x)
{
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			dest[i][j] = src[i][j];
}

char **get_generation(char **start, int generations, int *rowptr, int *colptr)
{
    char** cells = matrixdup(start, *rowptr, *colptr);

    if (!cells)
        return 0;
    
    for (int i = 0; i < generations; i++) {
        next_generation(cells, cells, rowptr, colptr);
	}
    
    return cells;
}