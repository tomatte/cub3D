/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_rays_to_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:16 by suzy              #+#    #+#             */
/*   Updated: 2023/08/02 14:23:33 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	draw_wide_line(t_mlx *mlx, t_line points, int size)
{
	int	i;

	i = 0;
	while (i++ < size)
	{
		draw_line(mlx, points);
		if (mlx->texture_index >= mlx->texture_height)
			mlx->texture_index = 0;
		points.x++;
		points.x2++;
	}
}

static void	transform_to_3d(t_mlx *mlx, int i)
{
	t_ray	*r;
	double	line_length;
	double	aux;
	int		line_mod = (int) (SCREEN_WIDTH / TOTAL_RAYS);
	double	nx;
	double	ny;
	double	line_begin;
	double	line_end;

	r = &mlx->ray;
	line_length = (SCREEN_HEIGHT * TILE_SIZE) / get_ray_distance(mlx);
	aux = r->y - line_length;
	if (aux < 0)
		aux = 0;
	ny = SCREEN_HEIGHT / 2;
	nx = i * line_mod;
	line_begin = ny + (line_length / 2);
	line_end = ny - (line_length / 2);
	draw_wide_line(mlx, points(nx, line_begin, nx, line_end), line_mod);
}

void	multiple_rays(t_mlx *mlx)
{
	double	ray_mod;
	double	sum;
	double	vision_angle;
	double	limit_angle;
	t_player	*p;
	t_ray		*r;
	int			i = -1;

	p = &mlx->player;
	r = &mlx->ray;
	vision_angle = degrees_to_radians(VISION_ANGLE);
	ray_mod = vision_angle / TOTAL_RAYS;
	limit_angle = vision_angle / 2;
	sum = limit_angle * -1;
	mlx->texture_index = 0;
	while (sum < limit_angle)
	{
		r->angle = normalize_angle(p->angle + sum);
		dda_ray(mlx);
		transform_to_3d(mlx, ++i);
		sum += ray_mod;
	}
}