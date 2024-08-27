#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include <include/conway.h>
#include <include/readfile.h>

#define TIME_UNIT	100000

int conway(char* file, int iterations, int dsec);

void help(FILE* stream)
{
	fputs("USAGE:\n"
		  "conway [-f FILE] [-i ITERATIONS] [-s INTERVAL]\n"
		  "\n"
		  "FLAGS:\n"
		  "\t-f\tfile where to read the configuration from\n"
		  "\t\t(default = a.dat)\n"
		  "\t-i\tnumber of iterations to visualize (default = 10)\n"
		  "\t-s\ttenth of seconds to wait between frames (default = 1)\n"
		  "\n"
		  "Written by Giovanni Zaccaria - LoZack19\n"
		  "\n"
		  "", stream);
}

int main(int argc, char* argv[])
{
	char* file = "a.dat";
	int iterations = 10;
	int dsec = 1;

	for (char c = 0; c != -1; c = getopt(argc, argv, "f:i:s:h")) {
		switch (c) {
			case 0:
				break;

			case '?':
				help(stderr);
				return -1;
			
			case 'f':
				if (optarg)
					file = optarg;
				else
					file = argv[optind];
				break;
			
			case 'i':
				if (optarg)
					iterations = strtol(optarg, NULL, 10);
				else
					iterations = strtol(argv[optind], NULL, 10);
				break;
			
			case 's':
				if (optarg)
					dsec = strtol(optarg, NULL, 10);
				else
					dsec = strtol(argv[optind], NULL, 10);
				break;
			
			case 'h':
				help(stdout);
				return 0;
			
			default:
				help(stderr);
				return -1;
		}
	}

	return conway(file, iterations, dsec);
}

int conway(char* file, int iterations, int dsec)
{
	int y, x;
	char** old_gen = init_matrix(file, &y, &x);
	if (!old_gen)
		return -1;

	hide_cursor();
	
	printmatrix(old_gen, y, x);
	char** new_gen = matrixdup(old_gen, y, x);

	for (int i = 1; i < iterations; i++) {
		clear();
		new_gen = next_generation(old_gen, new_gen, &y, &x);
		matrixcpy(old_gen, new_gen, y, x);

		printmatrix(new_gen, y, x);
		usleep(dsec * TIME_UNIT);
	}

	free_matrix(&new_gen, y);
	free_matrix(&old_gen, y);
	show_cursor();
	clear();

	return 0;
}