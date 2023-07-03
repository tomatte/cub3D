/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/03 17:01:02 by dbrandao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	draw_direction_line(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	draw_line(
		mlx,
		points(
			round(p->x + P_SIZE / 2),
			round(p->y + P_SIZE / 2),
			round(p->x + (P_SIZE / 2) + (p->delta_x * 20)),
			round(p->y + (P_SIZE / 2) + (p->delta_y * 20))
			)
		);
}

void	draw_player(t_mlx *mlx)
{
	t_player	*p;

	p = &mlx->player;
	square2(mlx, (int) round(p->x), (int) round(p->y), P_SIZE);
	draw_direction_line(mlx);
}

static void	erase_player(t_mlx *mlx)
{
	set_color(0x0);
	draw_player(mlx);
	set_color(DEFAULT_COLOR);
}

static void	draw_rays(t_mlx *mlx)
{
	t_player	*p;
	t_ray		*r;
	int			i;

	p = &mlx->player;
	r = &mlx->ray;
	set_color(0x0);
	draw_line(mlx, points(r->opx, r->opy, r->x, r->y));
	r->x = p->x;
	r->y = p->y;
	r->dx = cos(p->angle) * 20;
	r->dy = sin(p->angle) * 20;
	set_color(RED);
	i = 0;
	while (i++ < 30)
	{
		if (r->y < SCREEN_HEIGHT && r->x < SCREEN_WIDTH && r->x > 0 && r->y > 0)
		{
			r->y += r->dy;
			r->x += r->dx;
		}
	}
	r->opx = p->x + P_SIZE / 2;
	r->opy = p->y + P_SIZE / 2;
	draw_line(mlx, points(p->x + P_SIZE / 2, p->y + P_SIZE / 2, r->x, r->y));
	set_color(DEFAULT_COLOR);
}

int	keep_drawing(t_mlx *mlx)
{
	erase_player(mlx);
	update_player_position(mlx);
	draw_2d_blocks(mlx, 64);
	draw_player(mlx);
	draw_rays(mlx);
	put_image(mlx);
	return (1);
}
