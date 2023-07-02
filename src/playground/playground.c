/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/02 20:10:15 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


/* static void	draw_2_lines(t_mlx *mlx)
{
	draw_line2(mlx, points(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2), RED);
	set_color(RED);
	draw_line2(mlx, points(0, SCREEN_HEIGHT / 2 + 20, SCREEN_WIDTH, SCREEN_HEIGHT / 2 + 20), DEFAULT_COLOR);
} */

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
	while (++i <= size)
		draw_line(mlx, points(x, y + i, x2, y + i));
}

void	playground(t_mlx *mlx)
{
	square2(mlx, 100, 100, 8);
	put_image(mlx);
}
