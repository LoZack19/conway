# Conway's Game of Life

This project implements a simple visualization of Conway's Game of Life, a cellular automaton devised by the British mathematician John Horton Conway in 1970. The program reads an initial configuration from a file, then iteratively applies the rules of the Game of Life, displaying each generation on the terminal.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Options](#options)
- [Example](#example)
- [File Format](#file-format)
- [Contributing](#contributing)
- [License](#license)

## Installation

To compile the program, you need a C compiler like `gcc`. Clone this repository and compile the program using the following command:

```bash
gcc -o conway main.c -I./include -L./lib -lconway
```

Ensure that the `conway.h` and `readfile.h` header files are located in the `include` directory and any necessary libraries are in the `lib` directory.

## Usage

Run the program with the following command:

```bash
./conway [-f FILE] [-i ITERATIONS] [-s INTERVAL]
```

## Options

- `-f FILE` : Specifies the file from which to read the initial configuration. Default is `a.dat`.
- `-i ITERATIONS` : Sets the number of iterations (generations) to visualize. Default is 10.
- `-s INTERVAL` : Sets the time interval (in tenths of a second) between frames. Default is 1 (0.1 seconds).
- `-h` : Displays the help message.

## Example

```bash
./conway -f initial.dat -i 50 -s 2
```

This command runs the Game of Life using the initial configuration in `initial.dat`, iterating 50 times with a 0.2-second pause between each frame.

## File Format

The input file should contain a matrix where each cell is either `1` (alive) or `0` (dead). For example:

```
0 1 0 0 0
0 0 1 0 0
1 1 1 0 0
0 0 0 0 0
0 0 0 0 0
```

This represents a simple initial configuration for the Game of Life.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request with your changes. Make sure to follow the coding style and add appropriate tests for your changes.

---

Written by Giovanni Zaccaria - LoZack19
