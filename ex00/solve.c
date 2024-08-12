/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algebert <algebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:53 by algebert          #+#    #+#             */
/*   Updated: 2024/08/11 20:55:20 by algebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

// Recursive backtracking function
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
