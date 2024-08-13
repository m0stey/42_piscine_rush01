/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algebert <algebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:40:36 by algebert          #+#    #+#             */
/*   Updated: 2024/08/11 20:47:45 by algebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

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
