# Skyscrapers Puzzle Solver Documentation

## Overview
This C program solves a variant of the "Skyscrapers" puzzle using a recursive backtracking approach. In this puzzle, you fill a grid with numbers representing skyscraper heights based on visibility clues provided at the grid’s edges. The goal is to ensure the number of visible skyscrapers from each edge matches the given clues.

## Table of Contents
1. [Files and Structure](#files-and-structure)
2. [Definitions and Macros](#definitions-and-macros)
3. [Function Descriptions](#function-descriptions)
   - [Main Program (main.c)](#main-program-mainc)
   - [Solving Logic (solve.c)](#solving-logic-solvec)
   - [Helper Functions (helper.c)](#helper-functions-helperc)
4. [Execution Flow](#execution-flow)
5. [Error Handling](#error-handling)
6. [Memory Management](#memory-management)

## Files and Structure
The program is organized into four files:
- **rush.h**: Header file containing macros, includes, and function prototypes.
- **main.c**: Manages input parsing, grid initialization, and overall program execution.
- **solve.c**: Implements the core backtracking algorithm for solving the puzzle.
- **helper.c**: Contains helper functions that validate the visibility constraints.

### File Structure
```
- rush.h
- main.c
- solve.c
- helper.c
```

## Definitions and Macros
### rush.h
```c
#ifndef RUSH_H
# define RUSH_H

# define SIZE 6
# include <stdlib.h>
# include <unistd.h>

// Function prototypes
int is_error(int expression);
int parse_input(char *input, int *clues);
int init_grid(int ***grid);
int solve(int **grid, int row, int col, int *clues);
void print_grid(int **grid);
int is_valid_visibility(int **grid, int row, int col, int *clues);
int is_valid_number(int **grid, int row, int col, int num);
int row_left_to_right(int **grid, int row, int col, int *clues);
int row_right_to_left(int **grid, int row, int col, int *clues);
int col_top_to_bottom(int **grid, int row, int col, int *clues);
int col_bottom_to_top(int **grid, int row, int col, int *clues);

#endif // RUSH_H
```
- **SIZE**: Defines the grid size as 6x6.
- **Includes**:
  - `<stdlib.h>`: For memory allocation functions.
  - `<unistd.h>`: For I/O functions.
- **Function Prototypes**: Declares functions used across the different files.

## Function Descriptions

### Main Program (main.c)
#### `int main(int argc, char **argv)`
**Purpose**: Entry point of the program, handling initialization, error checking, and control flow.

**Parameters**:
- `int argc`: Number of command-line arguments.
- `char **argv`: Array of command-line arguments.

**Return**: Returns 0 on success, 1 on error.

**Description**:
- Parses input to extract clues.
- Initializes the grid.
- Solves the puzzle using backtracking.
- Prints the solved grid if successful.
- Frees allocated memory.

#### `int init_grid(int ***grid)`
**Purpose**: Initializes a 2D grid dynamically.

**Parameters**:
- `int ***grid`: Pointer to the grid to be initialized.

**Return**: Returns 0 on success, 1 on error.

**Description**:
- Allocates memory for the grid and sets all elements to 0.

#### `int is_error(int expression)`
**Purpose**: Handles error checking.

**Parameters**:
- `int expression`: Expression to evaluate.

**Return**: Returns 1 if an error occurs, otherwise 0.

**Description**:
- Prints "Error\n" and returns 1 if the expression evaluates to true.

#### `int parse_input(char *input, int *clues)`
**Purpose**: Parses the input string to extract visibility clues.

**Parameters**:
- `char *input`: Input string containing clues.
- `int *clues`: Array to store parsed clues.

**Return**: Returns 1 on successful parsing, 0 on failure.

**Description**:
- Extracts integers from the input string and stores them in the clues array.

#### `void print_grid(int **grid)`
**Purpose**: Prints the grid to the standard output.

**Parameters**:
- `int **grid`: Grid to be printed.

**Description**:
- Formats and prints the grid row by row.

### Solving Logic (solve.c)
#### `int solve(int **grid, int row, int col, int *clues)`
**Purpose**: Recursively solves the puzzle using backtracking.

**Parameters**:
- `int **grid`: The current state of the grid.
- `int row`: Current row in the grid.
- `int col`: Current column in the grid.
- `int *clues`: Array of visibility clues.

**Return**: Returns 1 if the puzzle is solved, otherwise 0.

**Description**:
- Attempts to place numbers in the grid while satisfying all constraints.
- If a number is valid, it recurses to the next cell.

#### `int is_valid_number(int **grid, int row, int col, int num)`
**Purpose**: Checks if a number can be placed in a cell without violating row or column constraints.

**Parameters**:
- `int **grid`: The current state of the grid.
- `int row`: Row index.
- `int col`: Column index.
- `int num`: Number to check.

**Return**: Returns 1 if the number is valid, otherwise 0.

**Description**:
- Ensures the number doesn’t already exist in the same row or column.

#### `int is_valid_visibility(int **grid, int row, int col, int *clues)`
**Purpose**: Checks if the current grid configuration satisfies the visibility constraints.

**Parameters**:
- `int **grid`: The current state of the grid.
- `int row`: Row index.
- `int col`: Column index.
- `int *clues`: Array of visibility clues.

**Return**: Returns 1 if visibility constraints are satisfied, otherwise 0.

**Description**:
- Validates visibility constraints when the last column or row is reached.

### Helper Functions (helper.c)
#### `int row_left_to_right(int **grid, int row, int col, int *clues)`
**Purpose**: Checks the visibility from the left side of a row.

**Parameters**:
- `int **grid`: The current state of the grid.
- `int row`: Row index.
- `int col`: Column index.
- `int *clues`: Array of visibility clues.

**Return**: Returns 1 if visibility matches the clue, otherwise 0.

#### `int row_right_to_left(int **grid, int row, int col, int *clues)`
**Purpose**: Checks the visibility from the right side of a row.

**Parameters**:
- `int **grid`: The current state of the grid.
- `int row`: Row index.
- `int col`: Column index.
- `int *clues`: Array of visibility clues.

**Return**: Returns 1 if visibility matches the clue, otherwise 0.

#### `int col_top_to_bottom(int **grid, int row, int col, int *clues)`
**Purpose**: Checks the visibility from the top of a column.

**Parameters**:
- `int **grid`: The current state of the grid.
- `int row`: Row index.
- `int col`: Column index.
- `int *clues`: Array of visibility clues.

**Return**: Returns 1 if visibility matches the clue, otherwise 0.

#### `int col_bottom_to_top(int **grid, int row, int col, int *clues)`
**Purpose**: Checks the visibility from the bottom of a column.

**Parameters**:
- `int **grid`: The current state of the grid.
- `int row`: Row index.
- `int col`: Column index.
- `int *clues`: Array of visibility clues.

**Return**: Returns 1 if visibility matches the clue, otherwise 0.

## Execution Flow
1. **Input Parsing**: The program expects a string of numbers (clues) as input.
   - Example: `"4 3 2 1 2 2 3 2 3 2 1 4 4 2 2 1 3 2 2 3 1 4 2 3 4 3 3 1"`
   - These clues are parsed and stored in an array.

2. **Grid Initialization**: A 2D grid of size `SIZE x SIZE` is dynamically allocated and initialized to 0.

3. **Puzzle Solving**:
   - The `solve()` function uses backtracking to place numbers in the grid.
   - Each placement is validated using `is_valid_number()` and `is_valid_visibility()` functions.
   - If a valid configuration is found, the grid is printed.

4. **Output**: The solved grid is printed to the standard output.

5. **Memory Cleanup**: All dynamically allocated memory is freed before the program exits.

## Error Handling
The program includes robust error checking for:
- Invalid input format or length.
- Memory allocation failures.

Errors are handled by printing `"Error\n"` and exiting with a return value of 1.

## Memory Management
- **Grid Allocation

**: The grid is allocated dynamically using `malloc()`.
- **Clues Array**: The array of clues is also dynamically allocated.
- **Memory Cleanup**: The program ensures all allocated memory is freed before termination.
