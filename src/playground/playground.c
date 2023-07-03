/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrandao <dbrandao@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:30:20 by dbrandao          #+#    #+#             */
/*   Updated: 2023/07/03 15:28:51 by dbrandao         ###   ########.fr       */
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

/* static void	draw_rays(t_mlx *mlx)
{
	t_ray		*ray;
	t_player	*p;
	const int	rays = 1;
	int			i;

	ray = &mlx->ray;
	p = &mlx->player;
	ray->ra = mlx->player.angle;
	i = 0;
	while (i++ < rays)
	{
		ray->dof = 0;
		ray->a_tan = -1 / tan(ray->ra);
		if (ray->ra > PI)
		{
			ray->y = (((int) p->y >> 6) << 6) - 0.0001;
			ray->x = (p->y - ray->y) * ray->a_tan + p->x;
			ray->yo = -64;
			ray->xo = -ray->yo * ray->a_tan;
		}
		if (ray->ra < PI)
		{
			ray->y = (((int) p->y >> 6) << 6) + 64;
			ray->x = (p->y - ray->y) * ray->a_tan + p->x;
			ray->yo = 64;
			ray->xo = -ray->yo * ray->a_tan;
		}
		if (ray->ra == PI || ray->ra == 0)
		{
			ray->x = p->x;
			ray->y = p->y;
			ray->dof = 8;
		}

		while (ray->dof < 8)
		{
			ray->mx = (int) (ray->x) >> 6;
			ray->my = (int) (ray->y) >> 6;
			ray->mp = ray->my * 10 + ray->mx;

			ray->x += ray->xo;
			ray->y += ray->yo;
			ray->dof += 1;
		}

		draw_line(mlx, points(p->x, p->y, ray->mx, ray->my));
	}
} */

int	keep_drawing(t_mlx *mlx)
{
	erase_player(mlx);
	update_player_position(mlx);
	draw_2d_blocks(mlx, 64);
	draw_player(mlx);
	//draw_rays(mlx);
	put_image(mlx);
	return (1);
}
