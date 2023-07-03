/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/03 02:09:23 by dbrandao         ###   ########.fr       */
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
	square2(mlx, (int) p->x, (int) p->y, P_SIZE);
	draw_line(
		mlx,
		points(
			p->x + P_SIZE / 2,
			p->y + P_SIZE / 2,
			p->x + (P_SIZE / 2) + (p->delta_x * 20),
			p->y + (P_SIZE / 2) + (p->delta_y * 20)
			)
		);
}

static void	move_limit(t_mlx *mlx)
{
	if (mlx->player.x < 0)
		mlx->player.x = 0;
	if (mlx->player.y < 0)
		mlx->player.y = 0;
	if (mlx->player.y + P_SIZE > SCREEN_HEIGHT)
		mlx->player.y = SCREEN_HEIGHT - P_SIZE;
	if (mlx->player.x + P_SIZE > SCREEN_WIDTH)
		mlx->player.x = SCREEN_WIDTH - P_SIZE;
}

static void	apply_move(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	p->angle += p->mv_angle_r;
	if (p->angle > 2 * PI)
		p->angle = 0;
	p->angle += p->mv_angle_l;
	if (p->angle < 0)
		p->angle = 2 * PI;
	p->delta_x = cos(p->angle);
	p->delta_y = sin(p->angle);
	if (p->mv_up)
	{
		p->x += p->delta_x / 6;
		p->y += p->delta_y / 6;
	}
	if (p->mv_down)
	{
		p->x -= p->delta_x / 6;
		p->y -= p->delta_y / 6;
	}
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
	square2(mlx, 100, 100, P_SIZE);
	put_image(mlx);
}
