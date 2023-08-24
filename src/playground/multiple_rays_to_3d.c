/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_rays_to_3d.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suzy <suzy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:22:16 by suzy              #+#    #+#             */
/*   Updated: 2023/08/24 04:07:07 by suzy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_texture	select_texture(t_mlx *mlx)
{
	t_ray		*r;

	r = &mlx->ray;
	if (is_north(r->x, r->y))
		mlx->texture_selected = NORTH;
	else if (is_east(r->x, r->y))
		mlx->texture_selected = EAST;
	else if (is_south(r->x, r->y))
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
	draw_line_textured(mlx, points(i, r->line_begin, i, r->line_end));
}

static void	save_old_ray(t_mlx *mlx)
{
	t_ray	*r;
	int		x;
	int		y;
	double diff_y;
	double diff_x;

	r = &mlx->ray;
	diff_y = positive(positive(r->rdy_col) - positive(r->rdy_row));
	diff_x = positive(positive(r->rdx_col) - positive(r->rdx_row));
	if (((int) r->column_x % TILE_SIZE == 0 || (int) (r->column_x + 1) % TILE_SIZE == 0)
		&& ((int) r->column_y % TILE_SIZE == 0 || (int) (r->column_y + 1) % TILE_SIZE == 0))
		return ;
	if (((int) r->row_x % TILE_SIZE == 0 || (int) (r->row_x + 1) % TILE_SIZE == 0)
		&& ((int) r->row_y % TILE_SIZE == 0 || (int) (r->row_y + 1) % TILE_SIZE) == 0)
		return ;
	if (looking_left(r->angle))
		x = (int)(r->x / TILE_SIZE);
	else
		x = (int)(ceil(r->x) / TILE_SIZE);
	if (looking_up(r->angle))
		y = (int)(r->y / TILE_SIZE);
	else
		y = (int)(ceil(r->y) / TILE_SIZE);
	if (x == mlx->block_x && y == mlx->block_y)
		return ;
	//mlx->block_x = x;
	//mlx->block_y = y;
	//mlx->old_ray = mlx->ray;
	mlx->old_texture = mlx->texture_selected;
	//r = &mlx->old_ray;
	//printf("old_ray_X: %lf  |  old_ray_Y: %lf\n", r->x, r->y);
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
		//save_old_ray(mlx);
		transform_to_3d(mlx, ++mlx->index_ray);
		mlx->angle_sum += ray_mod;
	}
}