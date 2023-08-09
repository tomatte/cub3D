/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_rays_to_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:16 by suzy              #+#    #+#             */
/*   Updated: 2023/08/09 13:20:45 by suzy             ###   ########.fr       */
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
	t_ray	*r;
	int		i;

	r = &mlx->ray;
	i = 0;
	while (i++ < size)
	{
		draw_line_textured(mlx, points, size);
		if (mlx->texture_index >= mlx->texture_height)
			mlx->texture_index = 0;
		points.x++;
		points.x2++;
		//printf("tile_map_x: %lf\n", r->tile_map_x);
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
	r->vertial_proportion = mlx->texture_height / line_length;
	r->tile_map_x = (int) round(r->old_x) % TILE_SIZE;
	r->distance = positive(r->old_x - r->x);
	r->horizontal_proportion = r->distance / line_mod;
	ny = SCREEN_HEIGHT / 2;
	nx = i * line_mod;
	//printf("distance: %lf  |  old_x: %lf  |  x: %lf\n", r->distance, r->old_x, r->x);
	//printf("nx: %lf  |  i: %d  |  line_mod: %d  |  line_length: %lf  |  horizontal_proportion: %lf\n", nx, i, line_mod, line_length, r->horizontal_proportion);
	line_begin = ny + (line_length / 2);
	line_end = ny - (line_length / 2);
	//printf("lengh: %lf  |  lengt/tile: %lf\n", line_length, line_length / TILE_SIZE);
	draw_wide_line(mlx, points(nx, line_begin, nx, line_end), line_mod);
}

void	multiple_rays(t_mlx *mlx)
{
	double		ray_mod;
	double		sum;
	double		vision_angle;
	double		limit_angle;
	t_player	*p;
	t_ray		*r;
	int			i;

	i = -1;
	p = &mlx->player;
	r = &mlx->ray;
	vision_angle = degrees_to_radians(VISION_ANGLE);
	ray_mod = vision_angle / TOTAL_RAYS;
	limit_angle = vision_angle / 2;
	sum = limit_angle * -1;
	mlx->texture_index = 0;

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
