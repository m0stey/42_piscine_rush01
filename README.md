This code is a C program that solves a variant of the "Skyscrapers" puzzle using backtracking. 
In this puzzle, you're given clues about how many skyscrapers are visible from the edges of a grid,
 and you must fill in the grid with numbers that represent the heights of skyscrapers. 
The code is structured in four files: main.c, solve.c, helper.c, and rush.h.

rush.h - Header File
The header file contains macro definitions, function prototypes, and necessary includes.

c
Copy code
#ifndef RUSH_H
# define RUSH_H

# define SIZE 6
# include <stdlib.h>
# include <unistd.h>

// Function prototypes
int		is_error(int expression);
int		parse_input(char *input, int *clues);
int		init_grid(int	***grid);
int		solve(int **grid, int row, int col, int *clues);
void	print_grid(int **grid);
int		is_valid_visibility(int **grid, int row, int col, int *clues);
int		is_valid_number(int **grid, int row, int col, int num);
int		row_left_to_right(int **grid, int row, int col, int *clues);
int		row_right_to_left(int **grid, int row, int col, int *clues);
int		col_top_to_bottom(int **grid, int row, int col, int *clues);
int		col_bottom_to_top(int **grid, int row, int col, int *clues);

#endif // RUSH_H
#define SIZE 6: Defines the size of the grid as 6x6.
#include <stdlib.h> and #include <unistd.h>: Includes the standard library and Unix standard library for memory allocation and I/O functions.
The function prototypes declare the functions implemented in the other C files, making them available for use across those files.
main.c - Main Program
The main file orchestrates the overall execution of the program.

c
Copy code
#include "rush.h"
#include "rush.h": Includes the header file, making all the macros, includes, and function prototypes available.
c
Copy code
int	main(int argc, char **argv)
{
	int	clues[SIZE * 4];
	int	**grid;
	int	i;

	if (is_error(argc != 2 || !(parse_input(argv[1], clues))))
		return (1);
	if (init_grid(&grid))
		return (1);
	if (solve(grid, 0, 0, clues))
		print_grid(grid);
	else
		is_error(1);
	i = 0;
	while (i < SIZE)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (0);
}
int clues[SIZE * 4];: Declares an array to store the clues given from the input.
int **grid;: Declares a double pointer to hold the dynamically allocated 2D grid.
int i;: Declares a loop counter.
Error Checking and Parsing Input:

c
Copy code
if (is_error(argc != 2 || !(parse_input(argv[1], clues))))
    return (1);
Checks if the number of arguments is not equal to 2 or if the input can't be parsed correctly into the clues array.
If an error occurs, it prints "Error\n" and returns 1.
Grid Initialization:

c
Copy code
if (init_grid(&grid))
    return (1);
Allocates memory for the grid. If allocation fails, it prints "Error\n" and returns 1.
Solve the Puzzle:

c
Copy code
if (solve(grid, 0, 0, clues))
    print_grid(grid);
else
    is_error(1);
Uses backtracking to solve the grid. If successful, it prints the grid; otherwise, it prints "Error\n".
Free Memory:

i = 0;
while (i < SIZE)
{
    free(grid[i]);
    i++;
}
free(grid);
Frees the memory allocated for the grid to avoid memory leaks.
Return 0:


return (0);
Returns 0 to indicate the program executed successfully.

int	init_grid(int	***grid)
{
	int	i;
	int	j;

	*grid = (int **)malloc(SIZE * sizeof(int *));
	if (is_error(*grid == NULL))
		return (1);
	i = 0;
	while (i < SIZE)
	{
		(*grid)[i] = (int *)malloc(SIZE * sizeof(int));
		if (is_error((*grid)[i] == NULL))
			return (1);
		j = 0;
		while (j < SIZE)
		{
			(*grid)[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}
*grid = (int **)malloc(SIZE * sizeof(int *));: Allocates memory for SIZE pointers to int, creating the first level of the 2D grid.
The following loop allocates memory for each row and initializes each cell to 0.
c
Copy code
int	is_error(int expression)
{
	if (expression)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	return (0);
}
This function checks if an error condition is met and prints "Error\n" if it is. It returns 1 if an error is present and 0 otherwise.

int	parse_input(char *input, int *clues)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i] >= '1' && input[i] <= ((char){'0' + SIZE}))
		{
			clues[j] = input[i] - '0';
			j++;
			if (input[i + 1] == ' ')
				i++;
		}
		else
			return (0);
		if (!(input[i] == '\0'))
			i++;
	}
	if (j == SIZE * 4)
		return (1);
	else
		return (0);
}
This function parses the input string to extract clues and store them in the clues array.
It checks that each character is within the valid range ('1' to 'SIZE') and correctly converts it to an integer.

void	print_grid(int **grid)
{
	char	output[((SIZE * 2) * SIZE)];
	int		pos;
	int		i;
	int		j;

	pos = 0;
	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			output[pos++] = grid[i][j] + '0';
			if (j != SIZE - 1)
				output[pos++] = ' ';
			j++;
		}
		output[pos++] = '\n';
		i++;
	}
	write(1, output, pos);
}
This function constructs a string representing the grid, which it then prints.
The grid is printed row by row, with each number separated by a space.
solve.c - Solving Logic
This file contains the recursive backtracking algorithm used to solve the puzzle.

int	solve(int **grid, int row, int col, int *clues)
{
	int	num;

	if (row == SIZE)
		return (1);
	if (col == SIZE)
		return (solve(grid, row + 1, 0, clues));
	num = 1;
	while (num <= SIZE)
	{
		if (is_valid_number(grid, row, col, num)
			&& is_valid_visibility(grid, row, col, clues))
		{
			grid[row][col] = num;
			if (solve(grid, row, col + 1, clues))
				return (1);
			grid[row][col] = 0;
		}
		num++;
	}
	return (0);
}
Base Case: If the current row is equal to SIZE, the grid is complete, so return 1.
Column Wrap-Around: If the column is equal to SIZE, move to the next row.
Backtracking:
Try each number from 1 to SIZE in the current cell.
If the number is valid according to the rules, set the cell to that number and recurse to the next cell.
If the solution is found, return 1; otherwise, reset the cell to 0 and try the next number.

int	is_valid_number(int **grid, int row, int col, int num)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		if (grid[row][i] == num || grid[i][col] == num)
			return (0);
		i++;
	}
	grid[row][col] = num;
	return (1);
}
This function checks if placing the number num in the grid at position [row][col] is valid by ensuring it doesn't violate any row or column constraints.
c
Copy code
int	is_valid_visibility(int **grid, int row, int col, int *clues)
{
	if (col == SIZE - 1)
	{
		if (!row_left_to_right(grid, row, col, clues))
			return (0);
		if (!row_right_to_left(grid, row, col, clues))
			return (0);
	}
	if (row == SIZE - 1)
	{
		if (!col_top_to_bottom(grid, row, col, clues))
			return (0);
		if (!col_bottom_to_top(grid, row, col, clues))
			return (0);
	}
	grid[row][col] = 0;
	return (1);
}
This function checks whether the current state of the grid satisfies the visibility constraints when the last column or row is reached.
helper.c - Visibility Validation
This file contains helper functions that validate the visibility constraints from different directions.


int	row_left_to_right(int **grid, int row, int col, int *clues)
{
	int	i;
	int	max;
	int	visible;

	i = 0;
	max = 0;
	visible = 0;
	while (i < SIZE)
	{
		if (grid[row][i] > max)
		{
			max = grid[row][i];
			visible++;
		}
		i++;
	}
	if (visible != clues[(SIZE * 2) + row])
	{
		grid[row][col] = 0;
		return (0);
	}
	return (1);
}
This function checks the visibility of skyscrapers from the left side of a row. 
It ensures the number of visible buildings matches the clue.


int	row_right_to_left(int **grid, int row, int col, int *clues)
{
	int	i;
	int	max;
	int	visible;

	i = SIZE - 1;
	max = 0;
	visible = 0;
	while (i >= 0)
	{
		if (grid[row][i] > max)
		{
			max = grid[row][i];
			visible++;
		}
		i--;
	}
	if (visible != clues[(SIZE * 3) + row])
	{
		grid[row][col] = 0;
		return (0);
	}
	return (1);
}
This function checks the visibility of skyscrapers from the right side of a row.

int	col_top_to_bottom(int **grid, int row, int col, int *clues)
{
	int	i;
	int	max;
	int	visible;

	visible = 0;
	max = 0;
	i = 0;
	while (i < SIZE)
	{
		if (grid[i][col] > max)
		{
			max = grid[i][col];
			visible++;
		}
		i++;
	}
	if (visible != clues[col])
	{
		grid[row][col] = 0;
		return (0);
	}
	return (1);
}
This function checks the visibility of skyscrapers from the top of a column.
c
Copy code
int	col_bottom_to_top(int **grid, int row, int col, int *clues)
{
	int	i;
	int	max;
	int	visible;

	visible = 0;
	max = 0;
	i = SIZE - 1;
	while (i >= 0)
	{
		if (grid[i][col] > max)
		{
			max = grid[i][col];
			visible++;
		}
		i--;
	}
	if (visible != clues[SIZE + col])
	{
		grid[row][col] = 0;
		return (0);
	}
	return (1);
}
This function checks the visibility of skyscrapers from the bottom of a column.
Summary
This program solves a "Skyscrapers" puzzle using a grid, where clues define how many buildings should be visible from each direction. It uses recursive backtracking to find a valid arrangement of skyscrapers that satisfies the constraints.

can you create a documentation out of it?
ChatGPT
Certainly! Here's a structured documentation for the C program that solves the "Skyscrapers" puzzle.

Skyscrapers Puzzle Solver Documentation
Overview
This program solves a variant of the "Skyscrapers" puzzle using a recursive backtracking approach. The puzzle involves filling a grid with numbers representing skyscraper heights, subject to visibility constraints provided by clues along the edges of the grid. The grid must satisfy these constraints such that the number of visible skyscrapers matches the given clues.

Table of Contents
Files and Structure
Definitions and Macros
Function Descriptions
Main Program (main.c)
Solving Logic (solve.c)
Helper Functions (helper.c)
Execution Flow
Error Handling
Memory Management
Files and Structure
The program is divided into four main files:

rush.h: Header file containing macros, includes, and function prototypes.
main.c: Main file that handles input parsing, grid initialization, and overall control flow.
solve.c: Contains the core backtracking algorithm for solving the puzzle.
helper.c: Implements helper functions for validating the visibility constraints based on the clues.
File Structure
text
Copy code
- rush.h
- main.c
- solve.c
- helper.c
Definitions and Macros
rush.h
c
Copy code
#ifndef RUSH_H
# define RUSH_H

# define SIZE 6
# include <stdlib.h>
# include <unistd.h>

// Function prototypes
int		is_error(int expression);
int		parse_input(char *input, int *clues);
int		init_grid(int	***grid);
int		solve(int **grid, int row, int col, int *clues);
void	print_grid(int **grid);
int		is_valid_visibility(int **grid, int row, int col, int *clues);
int		is_valid_number(int **grid, int row, int col, int num);
int		row_left_to_right(int **grid, int row, int col, int *clues);
int		row_right_to_left(int **grid, int row, int col, int *clues);
int		col_top_to_bottom(int **grid, int row, int col, int *clues);
int		col_bottom_to_top(int **grid, int row, int col, int *clues);

#endif // RUSH_H
SIZE: Defines the size of the grid as 6x6.
Includes:
stdlib.h: Provides functions for memory allocation.
unistd.h: Provides functions for I/O operations.
Function Prototypes: Declares all the functions used across the different files.
Function Descriptions
Main Program (main.c)
int main(int argc, char **argv)
Purpose: Entry point of the program, handles initialization, error checking, and controls the execution flow.
Parameters:
int argc: Number of command-line arguments.
char **argv: Array of command-line arguments.
Return: Returns 0 on successful execution, 1 on error.
Description:
Parses input to extract clues.
Initializes the grid.
Solves the puzzle using backtracking.
Prints the solved grid if successful.
Frees allocated memory.
int init_grid(int ***grid)
Purpose: Initializes a 2D grid dynamically.
Parameters:
int ***grid: Pointer to the grid to be initialized.
Return: Returns 0 on success, 1 on error.
Description:
Allocates memory for the grid and sets all elements to 0.
int is_error(int expression)
Purpose: Handles error checking.
Parameters:
int expression: Expression to evaluate.
Return: Returns 1 if an error occurs, otherwise 0.
Description:
Prints "Error\n" and returns 1 if the expression evaluates to true.
int parse_input(char *input, int *clues)
Purpose: Parses the input string to extract visibility clues.
Parameters:
char *input: Input string containing clues.
int *clues: Array to store parsed clues.
Return: Returns 1 on successful parsing, 0 on failure.
Description:
Extracts integers from the input string and stores them in the clues array.
void print_grid(int **grid)
Purpose: Prints the grid to the standard output.
Parameters:
int **grid: Grid to be printed.
Description:
Formats and prints the grid row by row.
Solving Logic (solve.c)
int solve(int **grid, int row, int col, int *clues)
Purpose: Recursively solves the puzzle using backtracking.
Parameters:
int **grid: The current state of the grid.
int row: Current row in the grid.
int col: Current column in the grid.
int *clues: Array of visibility clues.
Return: Returns 1 if the puzzle is solved, otherwise 0.
Description:
Attempts to place numbers in the grid while satisfying all constraints. If a number is valid, it recurses to the next cell.
int is_valid_number(int **grid, int row, int col, int num)
Purpose: Checks if a number can be placed in a given cell without violating row or column constraints.
Parameters:
int **grid: The current state of the grid.
int row: Row index.
int col: Column index.
int num: Number to check.
Return: Returns 1 if the number is valid, otherwise 0.
Description:
Ensures that the number num doesn't already exist in the same row or column.
int is_valid_visibility(int **grid, int row, int col, int *clues)
Purpose: Checks if the current grid configuration satisfies the visibility constraints.
Parameters:
int **grid: The current state of the grid.
int row: Row index.
int col: Column index.
int *clues: Array of visibility clues.
Return: Returns 1 if visibility constraints are satisfied, otherwise 0.
Description:
Validates the visibility constraints when the last column or row of the grid is reached.
Helper Functions (helper.c)
int row_left_to_right(int **grid, int row, int col, int *clues)
Purpose: Checks the visibility from the left side of a row.
Parameters:
int **grid: The current state of the grid.
int row: Row index.
int col: Column index.
int *clues: Array of visibility clues.
Return: Returns 1 if visibility matches the clue, otherwise 0.
int row_right_to_left(int **grid, int row, int col, int *clues)
Purpose: Checks the visibility from the right side of a row.
Parameters:
int **grid: The current state of the grid.
int row: Row index.
int col: Column index.
int *clues: Array of visibility clues.
Return: Returns 1 if visibility matches the clue, otherwise 0.
int col_top_to_bottom(int **grid, int row, int col, int *clues)
Purpose: Checks the visibility from the top of a column.
Parameters:
int **grid: The current state of the grid.
int row: Row index.
int col: Column index.
int *clues: Array of visibility clues.
Return: Returns 1 if visibility matches the clue, otherwise 0.
int col_bottom_to_top(int **grid, int row, int col, int *clues)
Purpose: Checks the visibility from the bottom of a column.
Parameters:
int **grid: The current state of the grid.
int row: Row index.
int col: Column index.
int *clues: Array of visibility clues.
Return: Returns 1 if visibility matches the clue, otherwise 0.
Execution Flow
Input Parsing: The program expects a single string of numbers (clues) as input.

Example: "4 3 2 1 2 2 3 2 3 2 1 4 4 2 2 1 3 2 2 3 1 4 2 3 4 3 3 1"
The clues are parsed and stored in an array.
Grid Initialization: A 2D grid of size SIZE x SIZE is dynamically allocated and initialized to 0.

Puzzle Solving:

The solve() function uses backtracking to place numbers in the grid.
Each placement is validated using the is_valid_number() and is_valid_visibility() functions.
If a valid configuration is found, the grid is printed.
Output: The solved grid is printed to the standard output.

Memory Cleanup: All dynamically allocated memory is freed before the program exits.

Error Handling
The program includes robust error checking:
Invalid input format or length.
Memory allocation failures.
Errors are handled by printing "Error\n" and exiting with a return value of 1.
Memory Management
Grid Allocation: Memory for the grid is allocated dynamically. Each row is an array of integers.
Memory Cleanup: Before the program exits, all allocated memory for the grid is freed to prevent memory leaks.
