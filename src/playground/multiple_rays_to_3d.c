/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_rays_to_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:16 by suzy              #+#    #+#             */
/*   Updated: 2023/08/26 14:22:36 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_texture	select_texture(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (is_north(r->angle, r->is_vertical))
		mlx->texture_selected = NORTH;
	else if (is_east(r->angle, r->is_vertical))
		mlx->texture_selected = EAST;
	else if (is_south(r->angle, r->is_vertical))
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
	if (r->is_vertical)
		texture->tile_map_x = (int) round(r->y) % TILE_SIZE;
	else
		texture->tile_map_x = (int) round(r->x) % (TILE_SIZE - 1);
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
	draw_line_textured(mlx, points(i, r->line_begin, i, r->line_end));
}

void	multiple_rays(t_mlx *mlx)
{
	double			ray_mod;
	double			vision_angle;
	double			limit_angle;
	t_player		*p;
	t_ray			*r;

	mlx->index_ray = -1;
	p = &mlx->player;
	r = &mlx->ray;
	vision_angle = degrees_to_radians(VISION_ANGLE);
	ray_mod = vision_angle / TOTAL_RAYS;
	limit_angle = vision_angle / 2;
	mlx->angle_sum = limit_angle * -1;
	while (mlx->angle_sum < limit_angle)
	{
		r->angle = normalize_angle(p->angle + mlx->angle_sum);
		dda_ray(mlx);
		transform_to_3d(mlx, ++mlx->index_ray);
		mlx->angle_sum += ray_mod;
	}
}
