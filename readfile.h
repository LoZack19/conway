#ifndef READFILE_H
#define READFILE_H

char** init_matrix(char* filename, int* _y, int* _x);

char* read_file(char* filename);

size_t strocc(const char* str, const char c);

off_t get_file_size(char* filename);

void canonicalize_buffer(char* buffer);

#endif /* READFILE_H */