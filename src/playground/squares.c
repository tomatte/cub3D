/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:31:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/02 14:49:30 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	square(t_mlx *mlx, int x, int y, int size)
{
	int	x2;
	int	y2;

	x2 = x + size - 1;
	y2 = y + size - 1;
	draw_line(mlx, points(x, y, x2, y));
	draw_line(mlx, points(x, y, x, y2));
	draw_line(mlx, points(x2, y, x2, y2));
	draw_line(mlx, points(x, y2, x2, y2));
}

void	square2(t_mlx *mlx, int x, int y, int size)
{
	int	i;
	int	x2;

	x2 = x + size - 1;
	i = -1;
	while (++i < size)
		draw_line(mlx, points(x, y + i, x2, y + i));
}

void	rectangle(t_mlx *mlx, int x, int y, int size_x, int size_y)
{
	int	i;
	int	x2;

	x2 = x + size_x - 1;
	i = -1;
	while (++i < size_y)
		draw_line(mlx, points(x, y + i, x2, y + i));
}

const int map1[11][15] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void	draw_2d_blocks(t_mlx *mlx, int size)
{
	int	i;
	int	j;
	int	x;
	int	y;

	x = 0;
	y = 0;
	i = -1;
	j = -1;
	while (++i < 11)
	{
		while (++j < 15)
		{
			if (map1[i][j])
				square2(mlx, x, y, size);
			else
				square(mlx, x, y, size);
			x += size;
		}
		y += size;
		x = 0;
		j = -1;
	}
}
