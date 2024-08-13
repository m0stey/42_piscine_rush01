/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algebert <algebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:23:31 by algebert          #+#    #+#             */
/*   Updated: 2024/08/11 20:47:46 by algebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

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

int	is_error(int expression)
{
	if (expression)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	return (0);
}

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

// Function to print the grid
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
