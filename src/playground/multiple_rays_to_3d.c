/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_rays_to_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:16 by suzy              #+#    #+#             */
/*   Updated: 2023/08/10 14:43:35 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

static void	next_index_w(t_mlx *mlx)
{
	mlx->ray_index_w++;
	if (mlx->ray_index_w > 64)
		mlx->ray_index_w = 0;
}

static void	draw_wide_line(t_mlx *mlx, t_line points, int size)
{
	t_texture	*texture;
	t_ray		*r;
	int			i;

	r = &mlx->ray;
	texture = &mlx->texture;
	i = 0;
	while (i++ < size)
	{
		draw_line_textured(mlx, points, size);
		points.x++;
		points.x2++;
		if (r->is_texture_inversed)
		{
			r->tile_map_x -= r->horizontal_proportion;
			if (r->tile_map_x < 0)
				r->tile_map_x = (TILE_SIZE - 1) - positive(r->tile_map_x);
		}
		else
			r->tile_map_x += r->horizontal_proportion;
		next_index_w(mlx);
	}
}

/* static void	transform_to_3d(t_mlx *mlx, int i)
{
	t_ray	*r;
	double	line_length;
	int		line_mod;
	double	nx;
	double	ny;
	double	line_begin;
	double	line_end;

	line_mod = (int)(SCREEN_WIDTH / TOTAL_RAYS);
	r = &mlx->ray;
	line_length = (SCREEN_HEIGHT * TILE_SIZE) / get_ray_distance(mlx);
	ny = SCREEN_HEIGHT / 2;
	nx = i * line_mod;
	printf("nx: %lf  |  i: %d  |  line_mod: %d\n", nx, i, line_mod);
	line_begin = ny + (line_length / 2);
	line_end = ny - (line_length / 2);
	//printf("lengh: %lf  |  lengt/tile: %lf\n", line_length, line_length / TILE_SIZE);
	draw_wide_line(mlx, points(nx, line_begin, nx, line_end), line_mod);
} */

static void	transform_to_3d(t_mlx *mlx, int i)
{
	t_ray		*r;
	t_texture	*texture;
	double		nx;
	double		ny;

	r = &mlx->ray;
	texture = &mlx->texture;
	r->line_mod = (int)(SCREEN_WIDTH / (TOTAL_RAYS - 1));
	r->line_length = (SCREEN_HEIGHT * TILE_SIZE) / get_ray_distance(mlx);
	r->vertial_proportion = texture->height / r->line_length;
	r->tile_map_x = (int) round(r->old_x) % TILE_SIZE;
	r->distance = positive(r->old_x - r->x);
	if (r->x < r->old_x || r->y < r->old_y)
		r->is_texture_inversed = 1;
	else
		r->is_texture_inversed = 0;
	if (r->distance == 0)
	{
		r->distance  = positive(r->old_y - r->y);
		r->tile_map_x = (int) round(r->old_y) % TILE_SIZE;
	}
	r->horizontal_proportion = r->distance / r->line_mod;
	ny = SCREEN_HEIGHT / 2;
	nx = i * r->line_mod;
	r->line_begin = ny + (r->line_length / 2);
	r->line_end = ny - (r->line_length / 2);
	draw_wide_line(mlx, points(nx, r->line_begin, nx, r->line_end), r->line_mod);
}

void	multiple_rays(t_mlx *mlx)
{
	double		ray_mod;
	double		sum;
	double		vision_angle;
	double		limit_angle;
	t_player	*p;
	t_ray		*r;
	t_texture	*texture;
	int			i;

	i = -1;
	p = &mlx->player;
	r = &mlx->ray;
	texture = &mlx->texture;
	vision_angle = degrees_to_radians(VISION_ANGLE);
	ray_mod = vision_angle / TOTAL_RAYS;
	limit_angle = vision_angle / 2;
	sum = limit_angle * -1;

	//test
	r->angle = normalize_angle(p->angle + sum);
	sum += ray_mod;
	dda_ray(mlx);
	r->old_x = r->x;
	r->old_y = r->y;
	while (sum < limit_angle)
	{
		r->angle = normalize_angle(p->angle + sum);
		dda_ray(mlx);
		transform_to_3d(mlx, ++i);
		r->old_x = r->x;
		r->old_y = r->y;
		sum += ray_mod;
	}
}
