#ifndef LIST_H
#define LIST_H

#define clear() fputs("\033[H\033[J", stdout)
#define hide_cursor() fputs("\e[?25l", stdout);
#define show_cursor() fputs("\e[?25h", stdout);

void printmatrix(char** matrix, int y, int x);

int cell_status(char **start, int y, int x, int limy, int limx);

char** next_generation(char **start, char **cells, int *rowptr, int *colptr);

void matrixcpy(char** dest, char** src, int y, int x);

void free_matrix(char ***matrix, int y);

char** matrixdup(char** src, int y, int x);

char** get_generation(char **start, int generations, int *rowptr, int *colptr);

#endif /* LIST_H */