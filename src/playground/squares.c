/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:31:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/03 13:31:56 by dbrandao         ###   ########.fr       */
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

void	draw_2d_blocks(t_mlx *mlx, int size)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (1)
	{
		if (x + size - 1 > SCREEN_WIDTH)
		{
			x = 0;
			y += size - 1;
		}
		if (y + size - 1 > SCREEN_HEIGHT)
			break ;
		square(mlx, x, y, size);
		x += size - 1;
	}
}
