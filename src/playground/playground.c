/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/03 00:45:46 by dbrandao         ###   ########.fr       */
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
	while (++i <= size)
		draw_line(mlx, points(x, y + i, x2, y + i));
}

void	draw_player(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	square2(mlx, (int) p->x, (int) p->y, 8);
	draw_line(mlx, points(p->x + 4, p->y + 4, p->x + 4 + (p->delta_x * 20), p->y + 4 + (p->delta_y * 20)));
}

static void	move_limit(t_mlx *mlx)
{
	if (mlx->player.x < 0)
		mlx->player.x = 0;
	if (mlx->player.y < 0)
		mlx->player.y = 0;
	if (mlx->player.y + 8 > SCREEN_HEIGHT)
		mlx->player.y = SCREEN_HEIGHT - 8;
	if (mlx->player.x + 8 > SCREEN_WIDTH)
		mlx->player.x = SCREEN_WIDTH - 8;
}

static void	apply_move(t_mlx *mlx)
{
	mlx->player.x += mlx->player.move_r;
	mlx->player.x += mlx->player.move_l;
	mlx->player.y += mlx->player.move_u;
	mlx->player.y += mlx->player.move_d;
}

int	keep_drawing(t_mlx *mlx)
{
	set_color(0x0);
	draw_player(mlx);
	set_color(DEFAULT_COLOR);
	apply_move(mlx);
	move_limit(mlx);
	draw_player(mlx);
	put_image(mlx);
	return (1);
}

void	playground(t_mlx *mlx)
{
	square2(mlx, 100, 100, 8);
	put_image(mlx);
}
