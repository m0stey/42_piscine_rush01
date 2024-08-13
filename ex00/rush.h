/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algebert <algebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:06:52 by algebert          #+#    #+#             */
/*   Updated: 2024/08/11 20:55:22 by algebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
# define RUSH_H

# define SIZE 4
# include <stdlib.h>
# include <unistd.h>

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