/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_rays_to_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:16 by suzy              #+#    #+#             */
/*   Updated: 2023/08/21 10:21:39 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_texture	select_texture(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (is_north(mlx))
		mlx->texture_selected = NORTH;
	else if (is_east(mlx))
		mlx->texture_selected = EAST;
	else if (is_south(mlx))
		mlx->texture_selected = SOUTH;
	else
		mlx->texture_selected = WEST;
	return (mlx->textures[mlx->texture_selected]);
}

static void	first_texture_calculation(t_mlx *mlx)
{
	t_texture	*texture;
	t_ray		*r;

	texture = &mlx->texture;
	r = &mlx->ray;
	//printf("rx: %lf  | ry: %lf\n", r->x, r->y);
	if (r->is_base_x)
		texture->tile_map_x = (int) round(r->y) % TILE_SIZE;
	else
		texture->tile_map_x = (int) round(r->x) % (TILE_SIZE - 1);
	//printf("map_x: %lf  |  map_y: %lf\n", texture->tile_map_x, texture->tile_map_y);
	texture->vertical_proportion = texture->height / r->line_length;
}

static void	transform_to_3d(t_mlx *mlx, int i)
{
	t_ray		*r;
	t_texture	*texture;
	double		nx;
	double		ny;

	r = &mlx->ray;
	mlx->texture = select_texture(mlx);
	texture = &mlx->texture;
	r->line_length = (SCREEN_HEIGHT * TILE_SIZE) / get_ray_distance(mlx);
	first_texture_calculation(mlx);
	ny = SCREEN_HEIGHT / 2;
	r->line_begin = ny + (r->line_length / 2);
	r->line_end = ny - (r->line_length / 2);
	draw_line_textured(mlx, points(i, r->line_begin, i, r->line_end), -9999999);
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
	while (sum < limit_angle)
	{
		r->angle = normalize_angle(p->angle + sum);
		dda_ray(mlx);
		transform_to_3d(mlx, ++i);
		sum += ray_mod;
	}
}
