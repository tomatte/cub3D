/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao < dbrandao@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 11:31:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/08/28 22:20:38 by dbrandao         ###   ########.fr       */
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

void	rectangle(t_mlx *mlx, t_vector vector, int size_x, int size_y)
{
	int	i;
	int	x2;

	x2 = vector.x + size_x - 1;
	i = -1;
	while (++i < size_y)
		draw_line(mlx, points(vector.x, vector.y + i, x2, vector.y + i));
}
